/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "Missile.h"
#include "GeoWars.h"

// -------------------------------------------------------------------------------

Player::Player()
{
    // configuração do objeto
    sprite = new Sprite("Resources/Player.png");
    speed  = new Vector(90.0f, 0.0f);
    BBox(new Circle(18.0f));
    MoveTo(game->CenterX(), game->CenterY());
    type = PLAYER;

    // configuração do gerador de partículas
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
    
    // movimenta objeto pelo seu vetor velocidade
    Translate(speed->XComponent() * 50.0f * gameTime, -speed->YComponent() * 50.0f * gameTime);

    // dispara míssil
    if (window->KeyPress(VK_SPACE))
    {
        GeoWars::audio->Play(FIRE);
        GeoWars::scene->Add(new Missile(), STATIC);
    }

    // atualiza calda do jogador
    tail->Config().angle = speed->Angle() + 180;
    tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
    tail->Update(gameTime);

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
    sprite->Draw(x, y, Layer::MIDDLE, 1.0f, -speed->Angle() + 90.0f);
    tail->Draw(Layer::LOWER, 1.0f);
}


// -------------------------------------------------------------------------------
