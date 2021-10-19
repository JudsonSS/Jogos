/**********************************************************************************
// Ball (Código Fonte)
// 
// Criação:     23 Nov 2011
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para uma bala de canhão
//
**********************************************************************************/

#include "Ball.h"
#include "Projectile.h"

// ------------------------------------------------------------------------------

bool Ball::airResistance = false;

// ------------------------------------------------------------------------------

Ball::Ball(Cannon * cannon)
{
    // cria sprite
    sprite = new Sprite("Resources/Ball.png");

    // define a velocidade da bola
    speed.RotateTo(cannon->direction.Angle());
    speed.ScaleTo(cannon->direction.Magnitude());
    
    // move para posição
    MoveTo(cannon->X() + 45 * cos(speed.Radians()), cannon->Y() - 45 * sin(speed.Radians()));
}

// ------------------------------------------------------------------------------

Ball::~Ball()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Ball::Update()
{    
    // a magnitude do vetor gravidade deve ser proporcional ao tempo do quadro
    // para que o resultado da soma vetorial seja independente da máquina

    // vetor gravidade
    Vector gravity { 270.0f, 200.0f * gameTime };

    // adiciona gravidade ao vetor velocidade
    speed.Add(gravity);

    // simula a resistência do ar com uma força no sentido oposto ao movimento
    if (airResistance)
    {
        // a resistência é 20% da velocidade
        Vector airForce(speed.Angle() + 180.0f, 0.20f * speed.Magnitude() * gameTime);

        // adiciona resistência do ar ao vetor velocidade
        speed.Add(airForce);
    }
    
    // move bola usando vetor resultante
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);
    
    // destrói bola se ela cair dentro d'água ou sair da tela
    if (X() < 0 || X() > window->Width() || Y() < 0 || Y() > window->Height() - 60)
    {
        Projectile::audio->Play(SPLASH);
        Projectile::scene->Delete();
    }
}

// -------------------------------------------------------------------------------

void Ball::Draw()
{
    sprite->Draw(x, y, z);
}

// -------------------------------------------------------------------------------
