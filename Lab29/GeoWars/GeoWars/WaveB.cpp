/**********************************************************************************
// WaveB (Código Fonte)
//
// Criação:		06 Ago 2019
// Atualização:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Cria uma onda de inimigos Blue
//
**********************************************************************************/

#include "WaveB.h"
#include "GeoWars.h"
#include "Blue.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

WaveB::WaveB() : posX(0, window->Width()), posY(0,window->Height()), secs(2.0f, 4.0f)
{
	// posição dos inimigos
	pX = posX.Rand();
	pY = posY.Rand();

	// atraso para a próxima onda 
	delay = secs.Rand();
}

// ------------------------------------------------------------------------------

WaveB::~WaveB()
{

}

// -------------------------------------------------------------------------------

void WaveB::Update()
{
	// contador de inimigos
	static uint counter = 8;

	// se passou o tempo de atraso
	if (timer.Elapsed(delay) && Hud::blues < 15)
	{
		if (counter > 0)
		{
			// toca som de nova onda
			GeoWars::audio->Play(BLUE);

			// adiciona nova inimigo
			GeoWars::scene->Add(new Blue(pX, pY, GeoWars::player), MOVING);

			delay = 0.450f;
			timer.Start();
			--counter;
		}
		else
		{
			// nova posição do inimigo
			pX = posX.Rand();
			pY = posY.Rand();

			// nova onda
			counter = 8;
			delay = secs.Rand();
			timer.Start();
		}
	}
}

// -------------------------------------------------------------------------------

void WaveB::Draw()
{
	
}

// -------------------------------------------------------------------------------
