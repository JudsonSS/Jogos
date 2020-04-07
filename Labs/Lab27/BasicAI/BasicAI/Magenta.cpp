/**********************************************************************************
// Magenta (Código Fonte)
// 
// Criação:		10 Out 2012
// Atualização:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Objeto faz um perseguição direta
//
**********************************************************************************/

#include "BasicAI.h"
#include "Magenta.h"
#include "Random.h" 
#include "Hud.h"
#include "Explosion.h"

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

	// incrementa contador
	++Hud::magentas;
}

// ---------------------------------------------------------------------------------

Magenta::~Magenta()
{
	delete sprite;
	delete bbox;

	// decrementa contador
	--Hud::magentas;
}

// -------------------------------------------------------------------------------

void Magenta::OnCollision(Object * obj)
{
	if (obj->Type() == MISSILE)
	{
		BasicAI::scene->Delete(obj, STATIC);
		BasicAI::scene->Delete(this, MOVING);
		BasicAI::scene->Add(new Explosion(x, y), STATIC);
		BasicAI::audio->Play(EXPLODE);
	}
}

// -------------------------------------------------------------------------------

void Magenta::Update()
{
	// ajusta ângulo do vetor 
	speed.angle = speed.Angle(x, y, player->X(), player->Y());
	Rotate(200 * gameTime);

	// movimenta objeto pelo seu vetor velocidade
	Translate(speed.XCom() * 60.0f * gameTime, -speed.YCom() * 60.0f * gameTime);
}

// -------------------------------------------------------------------------------