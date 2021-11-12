/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "Missile.h"
#include "BasicAI.h"
#include "Hud.h"

Image * Player::missile = nullptr;

// -------------------------------------------------------------------------------

Player::Player()
{
    // inicializa controle
    gamepad = new Controller();
    gamepadOn = gamepad->Initialize();

    // configuração do objeto
    sprite = new Sprite("Resources/Player.png");
    missile = new Image("Resources/Missile.png");
    speed.RotateTo(90.0f);
    speed.ScaleTo(0.0f);
    BBox(new Circle(18.0f));
    MoveTo(game->CenterX(), game->CenterY());
    type = PLAYER;

    // configuração do emissor de partículas
    Generator emitter;
    emitter.imgFile = "Resources/Spark.png";    // arquivo de imagem
    emitter.angle = 270.0f;                     // ângulo base do emissor
    emitter.spread = 25;                        // espalhamento em graus
    emitter.lifetime = 0.3f;                    // tempo de vida em segundos
    emitter.frequency = 0.010f;                 // tempo entre geração de novas partículas
    emitter.percentToDim = 0.6f;                // desaparece após 60% da vida
    emitter.minSpeed = 50.0f;                   // velocidade mínima das partículas
    emitter.maxSpeed = 100.0f;                  // velocidade máxima das partículas
    emitter.color.r = 1.0f;                     // componente Red da partícula 
    emitter.color.g = 1.0f;                     // componente Green da partícula 
    emitter.color.b = 1.0f;                     // componente Blue da partícula 
    emitter.color.a = 1.0f;                     // transparência da partícula

    // cria sistema de partículas
    tail = new Particles(emitter);
    tailCount = 0;

    // diparo habilitado
    firingAngle = 0.0f;
    keysPressed = false;
    axisCtrl = true;
    keysCtrl = true;
    start = 0;
    timer.Start();
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete sprite;
    delete missile;
    delete tail;
    delete gamepad;
}

// -------------------------------------------------------------------------------

bool Player::KeysTimed(bool pressed, float time)
{
    // se já passou o tempo para o próximo disparo
    if (keysCtrl)
    {
        // se há qualquer seta pressionada
        if (pressed)
        {
            keysCtrl = false;
            start = timer.Stamp();
            return true;
        }
    }
    // senão aguarda o momento certo
    else if (timer.Elapsed(start, time))
    {
        keysCtrl = true;
    }

    // teclas não pressionadas ou tempo não atingido
    return false;
}

// -------------------------------------------------------------------------------

bool Player::AxisTimed(int axisX, int axisY, float time)
{
    // se já passou o tempo para o próximo disparo
    if (axisCtrl)
    {
        // a magnitude é a distância do eixo para o seu centro
        float magnitude = Point::Distance(Point(0, 0), Point(float(gamepad->Axis(axisX)), float(gamepad->Axis(axisY))));

        // se há qualquer movimento no eixo
        if (magnitude > 0)
        {
            axisCtrl = false;
            start = timer.Stamp();
            return true;
        }
    }
    // senão aguarda o momento certo para testar
    else if (timer.Elapsed(start, time))
    {
        axisCtrl = true;
    }

    // eixo não acionado ou tempo não atingido
    return false;
}

// -------------------------------------------------------------------------------

void Player::Move(Vector && v)
{
    // soma vetor movimento (v) ao vetor velocidade
    speed.Add(v);

    // limita velocidade máxima
    if (speed.Magnitude() > 10.0f)
        speed.ScaleTo(10.0f);
}

// -------------------------------------------------------------------------------

void Player::Update()
{
    // magnitude do vetor aceleração
    float accel = 40.0f * gameTime;

    // -----------------
    // Controle
    // -----------------

    if (gamepadOn)
    {
        // atualiza estado das teclas e eixos do controle
        gamepad->UpdateState();

        // constrói vetor com base na posição do analógico esquerdo
        float ang = Line::Angle(Point(0, 0), Point(gamepad->Axis(AxisX) / 25.0f, gamepad->Axis(AxisY) / 25.0f));
        float mag = Point::Distance(Point(0, 0), Point(gamepad->Axis(AxisX) / 25.0f, gamepad->Axis(AxisY) / 25.0f));

        // nenhuma direção selecionada
        if (mag == 0)
        {
            // se a velocidade estiver muita baixa
            if (speed.Magnitude() < 0.1)
            {
                // pare de se movimentar imediatamente
                speed.ScaleTo(0.0f);
            }
            else
            {
                // some um vetor no sentido contrário para frear
                Move(Vector(speed.Angle() + 180.0f, 5.0f * gameTime));
            }
        }
        else
        {
            // movimente-se para a nova direção
            Move(Vector(ang, mag * gameTime));
        }

        // dispara míssil com o analógico direito
        if (AxisTimed(AxisRX, AxisRY, 0.150f))
        {
            float ang = Line::Angle(Point(0,0), Point(float(gamepad->Axis(AxisRX)), float(gamepad->Axis(AxisRY))));
            BasicAI::audio->Play(FIRE);
            BasicAI::scene->Add(new Missile(ang), STATIC);
        }
    }

    // -----------------
    // Teclado
    // -----------------

    else
    {
        // controla movimentação do jogador
        if (window->KeyDown('D') && window->KeyDown('W'))
            Move(Vector(45.0f, accel));
        else if (window->KeyDown('A') && window->KeyDown('W'))
            Move(Vector(135.0f, accel));
        else if (window->KeyDown('A') && window->KeyDown('S'))
            Move(Vector(225.0f, accel));
        else if (window->KeyDown('D') && window->KeyDown('S'))
            Move(Vector(315.0f, accel));
        else if (window->KeyDown('D'))
            Move(Vector(0.0f, accel));
        else if (window->KeyDown('A'))
            Move(Vector(180.0f, accel));
        else if (window->KeyDown('W'))
            Move(Vector(90.0f, accel));
        else if (window->KeyDown('S'))
            Move(Vector(270.0f, accel));
        else
            // se nenhuma tecla está pressionada comece a frear
            if (speed.Magnitude() > 0.1f)
                Move(Vector(speed.Angle() + 180.0f, 5.0f * gameTime));
            else
                // velocidade muita baixa, não use soma vetorial, apenas pare
                speed.ScaleTo(0.0f);

        // controla direção dos disparos
        if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_UP)) {
            keysPressed = true;
            firingAngle = 45.0f;
        } 
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_UP)) {
            keysPressed = true;
            firingAngle = 135.0f;
        }
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_DOWN)) {
            keysPressed = true;
            firingAngle = 225.0f;
        }
        else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_DOWN)) {
            keysPressed = true;
            firingAngle = 315.0f;
        }
        else if (window->KeyDown(VK_RIGHT)) {
            keysPressed = true;
            firingAngle = 0.0f;
        }
        else if (window->KeyDown(VK_LEFT)) {
            keysPressed = true;
            firingAngle = 180.0f;
        }
        else if (window->KeyDown(VK_UP)) {
            keysPressed = true;
            firingAngle = 90.0f;
        }
        else if (window->KeyDown(VK_DOWN)) {
            keysPressed = true;
            firingAngle = 270.0f;
        }
        else
        {
            keysPressed = false;
        }

        // dispara míssil
        if (KeysTimed(keysPressed, 0.150f))
        {
            BasicAI::audio->Play(FIRE);
            BasicAI::scene->Add(new Missile(firingAngle), STATIC);
        }
    }

    // movimenta objeto pelo seu vetor velocidade
    Translate(speed.XComponent() * 50.0f * gameTime, -speed.YComponent() * 50.0f * gameTime);

    // atualiza calda do jogador
    tail->Config().angle = speed.Angle() + 180;
    tail->Generate(x - 10 * cos(speed.Radians()), y + 10 * sin(speed.Radians()));
    tail->Update(gameTime);
    
    Hud::particles -= tailCount;
    tailCount = tail->Size();
    Hud::particles += tailCount;

    // restringe a área do jogo
    if (x < 50)
        MoveTo(50, y);
    if (y < 50)
        MoveTo(x, 50);
    if (x > game->Width() - 50)
        MoveTo(game->Width() - 50, y);
    if (y > game->Height() - 50)
        MoveTo(x, game->Height() - 50);
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, -speed.Angle() + 90.0f);
    tail->Draw(Layer::LOWER, 1.0f);
}

// -------------------------------------------------------------------------------
