/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:		21 Dez 2012
// Atualização:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Representa um míssil
//
**********************************************************************************/

#include "Missile.h"
#include "Patterns.h"

// ---------------------------------------------------------------------------------

Missile::Missile(Image * img)
{
	sprite = new Sprite(img);
	bbox = new Rect(-3, -8, 3, 8);
	vel = 450;
	type = MISSILE;
}

// ---------------------------------------------------------------------------------

Missile::~Missile()
{
	delete sprite;
	delete bbox;
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
