/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:		23 Nov 2011
// Atualização:	07 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define uma classe para um míssil
//
**********************************************************************************/

#include "Missile.h"
#include "WallHit.h"
#include "RunDemo.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

Player* & Missile::player = RunDemo::player;		// referência para o player

// ------------------------------------------------------------------------------

Missile::Missile()
{
	// inicializa sprite
	sprite = new Sprite("Resources/Missile.png");

	// cria bounding box
	bbox = new Circle(8);
	
	// inicializa velocidade
	speed.angle = player->speed->angle;
	speed.magnitude = 10.0f;
	
	// move para posição
	MoveTo(player->X() + 22 * cos(speed.Radians()), player->Y() - 22 * sin(speed.Radians()));
	RotateTo(-player->speed->angle + 90.0f);

	// define tipo
	type = MISSILE;

	// incrementa contador
	++Hud::missiles;
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
	delete sprite;
	delete bbox;

	// decrementa contador
	--Hud::missiles;
}

// -------------------------------------------------------------------------------

void Missile::Update()
{
	// move míssel com vetor resultante
	Translate(speed.XCom() * 90.0f * gameTime, -speed.YCom() * 90.0f * gameTime);

	// remove míssil da cena se ele sair da área de jogo
	if (x > game->Width() || x < 0 || y > game->Height() || y < 0)
	{
		// volume do som de destruição depende da distância para o jogador
		const float MaxDistance = 4406;
		const float BaseVolume = 0.8f;
		float distance = Point(x, y).Distance(Point(player->X(), player->Y()));
		float level = (MaxDistance - distance) / MaxDistance * BaseVolume;
		RunDemo::audio->Volume(HITWALL, level);
		RunDemo::audio->Play(HITWALL);

		// adiciona explosão na cena
		RunDemo::scene->Add(new WallHit(x,y), STATIC);

		// remove míssil da cena
		RunDemo::scene->Delete();
	}
}

// -------------------------------------------------------------------------------
