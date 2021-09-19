/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     07 Fev 2013
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Player usado em SoundDistance
//
**********************************************************************************/

#include "SoundDist.h"
#include "Player.h"
#include "Missile.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    explo   = new TileSet("Resources/Explosion.png", 64, 64, 5, 10);
    sprite  = new Sprite("Resources/Ship.png");
    missile = new Image("Resources/Missile.png");

    MoveTo(window->CenterX(), window->Height() - 50.0f, 0.0f);

    vel = 300;
    keyCtrl = false;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete explo;
    delete sprite;
    delete missile;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    // dispara um míssil com a barra de espaço
    if (keyCtrl && window->KeyDown(VK_SPACE))
    {
        // tamanho da nave é 24x20
        Missile * m = new Missile(missile, explo);
        m->MoveTo(x, y - 10, Layer::UPPER);
        SoundDist::scene->Add(m, MOVING);
        SoundDist::audio->Play(PULSE);
        keyCtrl = false;    
    }
    else if (window->KeyUp(VK_SPACE))
    {
        keyCtrl = true;
    }

    // desloca nave horizontalmente
    if (window->KeyDown(VK_RIGHT))
        Translate(vel * gameTime, 0);    
    if (window->KeyDown(VK_LEFT))
        Translate(-vel * gameTime, 0);

    // mantém nave dentro da janela
    if (x - sprite->Width()/2.0f < 0)
        MoveTo(sprite->Width()/2.0f, y);
    if (x + sprite->Width()/2.0f > window->Width())
        MoveTo(window->Width()-sprite->Width()/2.0f, y);
}

// ---------------------------------------------------------------------------------
