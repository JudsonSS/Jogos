/**********************************************************************************
// Magenta (Código Fonte)
// 
// Criação:		10 Out 2012
// Atualização:	07 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Objeto faz um perseguição direta
//
**********************************************************************************/

#include "SoftChase.h"
#include "Magenta.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Magenta::Magenta(float pX, float pY, Player * p)
{
	player = p;
	sprite = new Sprite("Resources/Magenta.png");
	bbox   = new Circle(18.0f);
	
	speed.angle = 0;
	speed.magnitude = 2.0f;
	
	MoveTo(pX, pY);
	type = MAGENTA;
}

// ---------------------------------------------------------------------------------

Magenta::~Magenta()
{
	delete sprite;
	delete bbox;
}

// -------------------------------------------------------------------------------

void Magenta::OnCollision(Object * obj)
{
	if (obj->Type() == MISSILE)
	{
		SoftChase::scene->Delete(obj, STATIC);
		SoftChase::scene->Delete(this, MOVING);
		SoftChase::audio->Play(EXPLODE);
	}
}

// -------------------------------------------------------------------------------

void Magenta::Update()
{
	// ajusta ângulo do vetor 
	speed.angle = speed.Angle(x, y, player->X(), player->Y());
	Rotate(200 * gameTime);

	// movimenta objeto pelo seu vetor velocidade
	Translate(speed.XCom() * 50.0f * gameTime, -speed.YCom() * 50.0f * gameTime);
}

// -------------------------------------------------------------------------------