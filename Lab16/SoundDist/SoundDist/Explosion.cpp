/**********************************************************************************
// Explosion (Código Fonte)
//
// Criação:		07 Fev 2013
// Atualização:	27 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Animação de uma explosão
//
**********************************************************************************/

#include "SoundDist.h"
#include "Explosion.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(TileSet * tiles)
{
	anim = new Animation(tiles, 0.015f, false);
	//bbox = new Circle(12.0f);
}

// ---------------------------------------------------------------------------------

Explosion::~Explosion()
{
	delete bbox;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Explosion::Update()
{
	anim->NextFrame();
	if (anim->Inactive())
		SoundDist::scene->Delete();	
}

// ---------------------------------------------------------------------------------