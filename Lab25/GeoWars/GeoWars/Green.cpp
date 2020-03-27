/**********************************************************************************
// Green (Código Fonte)
// 
// Criação:		15 Out 2012
// Atualização:	05 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Objeto faz uma fuga suavizada
//
**********************************************************************************/

#include "Green.h"
#include "GeoWars.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Green::Green(Player * p)
{
	player = p;
	sprite = new Sprite("Resources/Green.png");
	bbox   = new Circle(20.0f);
	speed  = new Vector(0, 2.0f);

	// mantém certa distância do jogador
	IntRand dist{ 300, 400 };
	distance = dist.Rand();

	// nasce em uma posição aleatória (canto inferior direito)
	FloatRand posX{ game->Width() - 50, game->Width() };
	FloatRand posY{ game->Height() - 50, game->Height() };
	MoveTo(posX.Rand(), posY.Rand());

	type = GREEN;
}

// ---------------------------------------------------------------------------------

Green::~Green()
{
	delete sprite;
	delete speed;
	delete bbox;
}

// -------------------------------------------------------------------------------

void Green::OnCollision(Object * obj)
{
	if (obj->Type() == MISSILE)
		GeoWars::scene->Delete(this, MOVING);
}

// -------------------------------------------------------------------------------

void Green::Update()
{
	// a magnitude do vetor target controla quão 
	// rápido o objeto converge para a direção do alvo
	Vector target = Vector(speed->Angle(x, y, player->X(), player->Y()), 10.0f * gameTime);
	
	// fugir se o player chegar muito perto
	if (speed->Distance(x, y, player->X(), player->Y()) < distance)
	{
		target.Rotate(180.0f);
		target.magnitude = 20.0f * gameTime;
	}

	speed->Add(target);
	
	// limita a magnitude da velocidade para impedir 
	// seu crescimento indefinido na soma vetorial
	if (speed->magnitude > 3)
		speed->magnitude = 3.0f;


	// move o objeto pelo seu vetor velocidade
	Translate(speed->XCom() * 50.0f * gameTime, -speed->YCom() * 50.0f * gameTime);
	Rotate(50 * gameTime);

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