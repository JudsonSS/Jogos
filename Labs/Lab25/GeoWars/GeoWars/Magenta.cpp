/**********************************************************************************
// Magenta (Código Fonte)
// 
// Criação:		10 Out 2012
// Atualização:	05 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Objeto faz um perseguição direta
//
**********************************************************************************/

#include "GeoWars.h"
#include "Magenta.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Magenta::Magenta(Player * p)
{
	player = p;
	sprite = new Sprite("Resources/Magenta.png");
	bbox   = new Circle(18.0f);
	speed  = new Vector(0, 2.0f);
	
	// move para uma posição aleatória (canto inferior esquerdo)
	FloatRand posX{ 300, 400 };
	FloatRand posY{ game->Height() - 400, game->Height() - 300 };
	MoveTo(posX.Rand(), posY.Rand());

	type = MAGENTA;
}

// ---------------------------------------------------------------------------------

Magenta::~Magenta()
{
	delete sprite;
	delete speed;
	delete bbox;
}

// -------------------------------------------------------------------------------

void Magenta::OnCollision(Object * obj)
{
	if (obj->Type() == MISSILE)
		GeoWars::scene->Delete(this, MOVING);
}

// -------------------------------------------------------------------------------

void Magenta::Update()
{
	// ajusta ângulo do vetor 
	speed->angle = speed->Angle(x, y, player->X(), player->Y());
	Rotate(200 * gameTime);

	// movimenta objeto pelo seu vetor velocidade
	Translate(speed->XCom() * 50.0f * gameTime, -speed->YCom() * 50.0f * gameTime);
}

// -------------------------------------------------------------------------------