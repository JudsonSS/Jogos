/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:		23 Nov 2011
// Atualização:	03 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define uma classe para um míssil
//
**********************************************************************************/

#include "Missile.h"
#include "WallHit.h"
#include "BasicAI.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

Player* & Missile::player = BasicAI::player;		// referência para o player

// ------------------------------------------------------------------------------

Missile::Missile(float angle)
{
	// inicializa sprite
	sprite = new Sprite("Resources/Missile.png");

	// cria bounding box
	bbox = new Circle(8);
	
	// inicializa velocidade
	speed.angle = angle;
	speed.magnitude = 10.0f;
	
	// move para posição
	MoveTo(player->X() + 40 * cos(speed.Radians()), player->Y() - 40 * sin(speed.Radians()));
	RotateTo(-speed.angle + 90.0f);

	// define tipo
	type = MISSILE;

	// incrementa contagem
	++Hud::missiles;
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
	delete sprite;
	delete bbox;

	// decrementa contagem
	--Hud::missiles;
}

// -------------------------------------------------------------------------------

void Missile::Update()
{
	// move míssel com vetor resultante
	Translate(speed.XCom() * 90.0f * gameTime, -speed.YCom() * 90.0f * gameTime);

	// remove míssil da cena se ele sair da área de jogo
	if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
	{
		// volume do som de destruição depende da distância para o jogador
		const float MaxDistance = 4406;
		const float BaseVolume = 0.8f;
		float distance = Point(x, y).Distance(Point(player->X(), player->Y()));
		float level = (MaxDistance - distance) / MaxDistance * BaseVolume;
		BasicAI::audio->Volume(HITWALL, level);
		BasicAI::audio->Play(HITWALL);

		// adiciona explosão na cena
		BasicAI::scene->Add(new WallHit(x,y), STATIC);

		// remove míssil da cena
		BasicAI::scene->Delete();
	}
}

// -------------------------------------------------------------------------------
