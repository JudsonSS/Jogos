/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:     21 Dez 2012
// Atualização: 10 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Representa um míssil
//
**********************************************************************************/

#include "Missile.h"
#include "Patterns.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

Missile::Missile(float pX, float pY)
{
    sprite = new Sprite(Player::missile);
    MoveTo(pX, pY);
    BBox(new Rect(-3, -8, 3, 8));
    vel = 450;
    type = MISSILE;
}

// ---------------------------------------------------------------------------------

Missile::~Missile()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Missile::Update()
{
    // míssil se move apenas no eixo y
    Translate(0, -vel * gameTime);

    // remove mísseis que saem da janela
    if (y < 0)
        Patterns::scene->Delete();
}

// ---------------------------------------------------------------------------------
