/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:		21 Dez 2012
// Atualização: 28 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Mísseis do jogo Galaga
//
**********************************************************************************/

#include "Missile.h"
#include "Galaga.h"

// ---------------------------------------------------------------------------------

Missile::Missile(Image * img)
{
	sprite = new Sprite(img);
	vel    = 250;
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
		Galaga::scene->Remove();
}

// ---------------------------------------------------------------------------------
