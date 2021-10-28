/**********************************************************************************
// Explosion (Código Fonte)
//
// Criação:     07 Fev 2013
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Animação de uma explosão
//
**********************************************************************************/

#include "Explosion.h"
#include "Asteroids.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(float posX, float posY)
{
    anim = new Animation(Asteroids::exploSet, 0.010f, false);
    MoveTo(posX, posY);
}

// ---------------------------------------------------------------------------------

Explosion::~Explosion()
{
    delete anim;
}

// ---------------------------------------------------------------------------------

void Explosion::Update()
{
    anim->NextFrame();

    if (anim->Inactive())
        Asteroids::scene->Delete();    
}

// ---------------------------------------------------------------------------------