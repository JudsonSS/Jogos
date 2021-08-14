/**********************************************************************************
// Shank (Código Fonte)
//
// Criação:     21 Dez 2012
// Atualização: 14 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define personagem Shank como um objeto do jogo
//
**********************************************************************************/

#include "Shank.h"

// ---------------------------------------------------------------------------------

Shank::Shank()
{
    sprite = new Sprite("Resources/Shank.png");
    MoveTo(80.0f, 90.0f, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Shank::~Shank()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Shank::Update()
{
    if (window->KeyDown(VK_LEFT))
        x -= 50.0f * gameTime;
    if (window->KeyDown(VK_RIGHT))
        x += 50.0f * gameTime;
    if (window->KeyDown(VK_UP))
        y -= 50.0f * gameTime;
    if (window->KeyDown(VK_DOWN))
        y += 50.0f * gameTime;
}

// ---------------------------------------------------------------------------------

void Shank::Draw()
{
    sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
