/**********************************************************************************
// Explosion (Código Fonte)
//
// Criação:     07 Fev 2013
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Animação de uma explosão
//
**********************************************************************************/

#include "Explosion.h"
#include "Inertia.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(TileSet * tiles)
{
    anim = new Animation(tiles, 0.020f, false);
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
        Inertia::scene->Delete();    
}

// ---------------------------------------------------------------------------------