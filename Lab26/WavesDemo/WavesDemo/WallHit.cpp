/**********************************************************************************
// WallHit (Código Fonte)
// 
// Criação:		03 Ago 2019
// Atualização:	07 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#include "WavesDemo.h"
#include "WallHit.h"
#include "Random.h"

// ---------------------------------------------------------------------------------

WallHit::WallHit(float pX, float pY)
{
	// calcula ângulo base e ajusta coordenadas da explosão
	float base;
	if (pX < 0)
	{
		base = 0.0f;
		pX = 0;
	}
	else if (pX > game->Width())
	{
		base = 180.0f;
		pX = game->Width();
	}
	else if (pY < 0)
	{
		base = 270.0f;
		pY = 0;
	}
	else
	{
		base = 90.0f;
		pY = game->Height();
	}

	// número aleatório entre 0 e 1
	FloatRand color{ 0, 1 };
	
	// configura emissor de partículas
	Emitter explosion;
	explosion.imgFile   = "Resources/Star.png";		// arquivo de imagem
	explosion.angle     = base;						// direção da explosão
	explosion.spread    = 80.0f;					// espalhamento em graus
	explosion.lifeTime  = 1.0f;						// tempo de vida em segundos
	explosion.genTime   = 0.000f;					// tempo entre geração de novas partículas
	explosion.percToDim = 0.6f;						// desaparece após 60% da vida
	explosion.minSpeed  = 25.0f;					// velocidade mínima das partículas
	explosion.maxSpeed  = 250.0f;					// velocidade máxima das partículas
	explosion.r = color.Rand();						// cor da partícula entre 0 e 1
	explosion.g = color.Rand();						// cor da partícula entre 0 e 1
	explosion.b = color.Rand();						// cor da partícula entre 0 e 1
	explosion.a = 1.0f;								// transparência da partícula

	// cria sistema de partículas
	starsGen = new Particles(explosion);

	// gera 50 partículas na posição do mouse
	starsGen->Generate(pX, pY, 25);
	type = WALLHIT;
}

// ---------------------------------------------------------------------------------

WallHit::~WallHit()
{
	delete starsGen;
}

// -------------------------------------------------------------------------------

void WallHit::Update()
{
	// atualiza posição de cada partícula
	starsGen->Update(gameTime);

	// remove da cena quando todas as partículas estão inativas
	if (starsGen->Inactive())
		WavesDemo::scene->Delete();
}

// -------------------------------------------------------------------------------