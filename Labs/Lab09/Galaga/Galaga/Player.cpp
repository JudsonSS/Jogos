/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:     21 Dez 2012
// Atualização: 18 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Player do jogo Galaga
//
**********************************************************************************/

#include "Player.h"
#include "Missile.h"
#include "Galaga.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    sprite  = new Sprite("Resources/Nave.png");
    missile = new Image ("Resources/Missile.png");

    MoveTo(window->CenterX() - sprite->Width()/2.0f, window->Height() - 50.0f, Layer::FRONT);
    vel = 160;
    keyCtrl = true;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete sprite;
    delete missile;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    // dispara um míssil com a barra de espaço
    if (keyCtrl && window->KeyDown(VK_SPACE))
    {
        // tamanho do míssel é 26x30
        Missile * m = new Missile(missile);
        m->MoveTo(x + sprite->Width()/2.0f - 2, y, Layer::UPPER);
        Galaga::scene->Add(m);
        keyCtrl = false;
    }
    else if (window->KeyUp(VK_SPACE))
    {
        // habilita disparo de míssil se tecla for liberada
        keyCtrl = true;
    }

    // desloca nave horizontalmente
    if (window->KeyDown(VK_RIGHT))
        Translate(vel * gameTime, 0);
    if (window->KeyDown(VK_LEFT))
        Translate(-vel * gameTime, 0);

    // mantém nave dentro da janela
    if (x < 0)
        MoveTo(0, y);
    if (x + sprite->Width() > window->Width())
        MoveTo(float(window->Width() - sprite->Width()), y);
}

// ---------------------------------------------------------------------------------
