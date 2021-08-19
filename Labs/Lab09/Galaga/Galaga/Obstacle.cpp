/**********************************************************************************
// Obstacle (Código Fonte)
// 
// Criação:     19 Dez 2012
// Atualização: 14 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Obstáculos do jogo Frogger
//
**********************************************************************************/

#include "Obstacle.h"

// ---------------------------------------------------------------------------------

Obstacle::Obstacle(Image * img, float speed)
{
    sprite = new Sprite(img);
    vel    = speed;
}

// ---------------------------------------------------------------------------------

Obstacle::~Obstacle()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Obstacle::Update()
{
    // objeto caminha no eixo x
    Translate(-vel * gameTime, 0.0f);
    
    // passa objeto de um lado da tela para o outro
    if (int(x) + sprite->Width() < 0)
        MoveTo(float(window->Width() + sprite->Width()), y);
}

// ---------------------------------------------------------------------------------
