/**********************************************************************************
// Debris (Código Fonte)
//
// Criação:     07 Fev 2013
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Animação de explosão
//
**********************************************************************************/

#include "Debris.h"
#include "Asteroids.h"

// ---------------------------------------------------------------------------------

Debris::Debris(float posX, float posY)
{
    anim = new Animation(Asteroids::debriSet, 0.060f, false);
    MoveTo(posX, posY);
}

// ---------------------------------------------------------------------------------

Debris::~Debris()
{
    delete anim;
}

// ---------------------------------------------------------------------------------

void Debris::Update()
{
    anim->NextFrame();

    if (anim->Inactive())
        Asteroids::scene->Delete();    
}

// ---------------------------------------------------------------------------------