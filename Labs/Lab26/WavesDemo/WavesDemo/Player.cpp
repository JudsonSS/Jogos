/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "Missile.h"
#include "WavesDemo.h"

// -------------------------------------------------------------------------------

Player::Player()
{
    // inicializa controle
    gamepad = new Controller();
    gamepadOn = gamepad->Initialize();

    // configuração do jogador
    sprite = new Sprite("Resources/Player.png");
    speed  = new Vector(90.0f, 0.0f);
    BBox(new Circle(18.0f));
    MoveTo(game->CenterX(), game->CenterY());
    type = PLAYER;

    // configuração do emissor de partículas
    Generator emitter;
    emitter.imgFile = "Resources/Spark.png";    // arquivo de imagem
    emitter.angle = 270.0f;                     // ângulo base do emissor
    emitter.spread = 50;                        // espalhamento em graus
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
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete sprite;
    delete speed;
    delete tail;
    delete gamepad;
}

// -------------------------------------------------------------------------------

void Player::Move(Vector && v)
{
    speed->Add(v);

    // limita velocidade máxima
    if (speed->Magnitude() > 10.0f)
        speed->ScaleTo(10.0f);

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
        gamepad->UpdateState();

        float ang = Line::Angle(Point(0, 0), Point(gamepad->Axis(AxisX) / 25.0f, gamepad->Axis(AxisY) / 25.0f));
        float mag = Point::Distance(Point(0, 0), Point(gamepad->Axis(AxisX) / 25.0f, gamepad->Axis(AxisY) / 25.0f));

        // nenhuma direção selecionada
        if (mag == 0)
        {
            // se a velocidade estiver muita baixa
            if (speed->Magnitude() < 0.1)
            {
                // apenas pare
                speed->ScaleTo(0.0f);
            }
            else
            {
                // comece a frear
                Move(Vector(speed->Angle() + 180.0f, 5.0f * gameTime));
            }
        }
        else
        {
            // ande na direção selecionada
            Move(Vector(ang, mag * gameTime));
        }

        // dispara míssil
        if (gamepad->ButtonPress(0))
        {
            WavesDemo::audio->Play(FIRE);
            WavesDemo::scene->Add(new Missile(), STATIC);
        }
    }

    // -----------------
    // Teclado
    // -----------------

    else
    {
        // modifica vetor velocidade do player
        if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_UP))
            Move(Vector(45.0f, accel));
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_UP))
            Move(Vector(135.0f, accel));
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_DOWN))
            Move(Vector(225.0f, accel));
        else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_DOWN))
            Move(Vector(315.0f, accel));
        else if (window->KeyDown(VK_RIGHT))
            Move(Vector(0.0f, accel));
        else if (window->KeyDown(VK_LEFT))
            Move(Vector(180.0f, accel));
        else if (window->KeyDown(VK_UP))
            Move(Vector(90.0f, accel));
        else if (window->KeyDown(VK_DOWN))
            Move(Vector(270.0f, accel));
        else
            // se nenhuma tecla está pressionada comece a frear
            if (speed->Magnitude() > 0.1f)
                Move(Vector(speed->Angle() + 180.0f, 5.0f * gameTime));
            else
                // velocidade muita baixa, não use soma vetorial, apenas pare
                speed->ScaleTo(0.0f);

        // dispara míssil
        if (window->KeyPress(VK_SPACE))
        {
            WavesDemo::audio->Play(FIRE);
            WavesDemo::scene->Add(new Missile(), STATIC);
        }
    }

    // movimenta objeto pelo seu vetor velocidade
    Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);

    // atualiza calda do jogador
    tail->Config().angle = speed->Angle() + 180;
    tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
    tail->Update(gameTime);

    // restringe a área do jogo
    if (x < 0)
        MoveTo(0, y);
    if (y < 0)
        MoveTo(x, 0);
    if (x > game->Width())
        MoveTo(game->Width(), y);
    if (y > game->Height())
        MoveTo(x, game->Height());
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, -speed->Angle() + 90.0f);
    tail->Draw(Layer::LOWER, 1.0f);
}


// -------------------------------------------------------------------------------
