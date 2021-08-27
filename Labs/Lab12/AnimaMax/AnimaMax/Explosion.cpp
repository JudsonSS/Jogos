/**********************************************************************************
// Explosion (Código Fonte)
//
// Criação:     20 Jan 2013
// Atualização: 27 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Animação de uma explosão
//
**********************************************************************************/

#include "Explosion.h"
#include "AnimaMax.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(TileSet * tiles)
{
    anim = new Animation(tiles, 0.060f, false);
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
        AnimaMax::scene->Delete();
}

// ---------------------------------------------------------------------------------