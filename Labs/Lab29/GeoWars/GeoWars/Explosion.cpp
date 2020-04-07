/**********************************************************************************
// Explosion (Código Fonte)
// 
// Criação:		17 Mar 2013
// Atualização:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#include "GeoWars.h"
#include "Explosion.h"
#include "Random.h"
#include "Hud.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(float pX, float pY)
{
	// número aleatório entre 0 e 1
	FloatRand color{ 0, 1 };

	// configura emissor de partículas
	Emitter explosion;
	explosion.imgFile   = "Resources/Explo.png";	// arquivo de imagem
	explosion.angle     = 0.0f;						// direção da explosão
	explosion.spread    = 180.0f;					// espalhamento em graus
	explosion.lifeTime  = 1.5f;						// tempo de vida em segundos
	explosion.genTime   = 0.000f;					// tempo entre geração de novas partículas
	explosion.percToDim = 0.8f;						// desaparece após 60% da vida
	explosion.minSpeed  = 25.0f;					// velocidade mínima das partículas
	explosion.maxSpeed  = 250.0f;					// velocidade máxima das partículas
	explosion.r = color.Rand();						// cor da partícula entre 0 e 1
	explosion.g = color.Rand();						// cor da partícula entre 0 e 1
	explosion.b = color.Rand();						// cor da partícula entre 0 e 1
	explosion.a = 1.0f;								// transparência da partícula

	// cria sistema de partículas
	starsGen = new Particles(explosion);

	// gera 25 partículas na posição indicada
	starsGen->Generate(pX, pY, 50);
	type = EXPLOSION;

	// incrementa contagem de partículas
	Hud::particles += 50;
}

// ---------------------------------------------------------------------------------

Explosion::~Explosion()
{
	delete starsGen;

	// decrementa contagem de partículas
	Hud::particles -= 50;
}

// -------------------------------------------------------------------------------

void Explosion::Update()
{
	// atualiza posição de cada partícula
	starsGen->Update(gameTime);

	// remove da cena quando todas as partículas estão inativas
	if (starsGen->Inactive())
		GeoWars::scene->Delete();
}

// -------------------------------------------------------------------------------