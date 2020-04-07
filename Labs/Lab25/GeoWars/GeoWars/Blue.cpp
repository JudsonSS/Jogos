/**********************************************************************************
// Blue (Código Fonte)
// 
// Criação:		10 Out 2012
// Atualização:	05 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Objeto faz uma perseguição suavizada
//
**********************************************************************************/

#include "GeoWars.h"
#include "Blue.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Blue::Blue(Player * p)
{
	player = p;
	sprite = new Sprite("Resources/Blue.png");
	bbox   = new Circle(20.0f);
	speed  = new Vector(0, 2.0f);
	
	// move para uma posição aleatória (canto superior direito)
	FloatRand posX{ game->Width() - 400, game->Width() - 300 };
	FloatRand posY{ 300, 400 };
	MoveTo(posX.Rand(), posY.Rand());
	
	factor = -0.25f;
	type = BLUE;
}

// ---------------------------------------------------------------------------------

Blue::~Blue()
{
	delete sprite;
	delete speed;
	delete bbox;
}

// -------------------------------------------------------------------------------

void Blue::OnCollision(Object * obj)
{
	if (obj->Type() == MISSILE)
		GeoWars::scene->Delete(this, MOVING);
}

// -------------------------------------------------------------------------------

void Blue::Update()
{
	// a magnitude do vetor 'target' controla quão 
	// rápido o objeto converge para a direção do alvo
	Vector target = Vector(speed->Angle(x, y, player->X(), player->Y()), 2.0f * gameTime);
	speed->Add(target);
	
	// limita a magnitude da velocidade para impedir 
	// que ela cresça indefinidamente pelo soma vetorial
	if (speed->magnitude > 2.5)
		speed->magnitude = 2.5f;

	// move o objeto pelo seu vetor velocidade
	Translate(speed->XCom() * 50.0f * gameTime, -speed->YCom() * 50.0f * gameTime);

	// aplica fator de escala
	Scale(1.0f + factor * gameTime);

	// amplia e reduz objeto
	if (scale < 0.85f)
		factor = 0.25f;
	if (scale > 1.00f)
		factor = -0.25f;

	// mantém o objeto dentro do mundo do jogo
	if (x < 50)
		MoveTo(50, y);
	if (y < 50)
		MoveTo(x, 50);
	if (x > game->Width() - 50)
		MoveTo(game->Width() - 50, y);
	if (y > game->Height() - 50)
		MoveTo(x, game->Height() - 50);
}

// -------------------------------------------------------------------------------