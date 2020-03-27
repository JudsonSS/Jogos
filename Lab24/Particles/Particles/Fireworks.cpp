/**********************************************************************************
// Fireworks (Código Fonte)
// 
// Criação:		17 Mar 2013
// Atualização:	31 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#include "Refinery.h"
#include "Fireworks.h"

// ---------------------------------------------------------------------------------

Fireworks::Fireworks()
{
	// configura emissor de partículas
	Emitter explosion;
	explosion.imgFile   = "Resources/Star.png";		// arquivo de imagem
	explosion.angle     = float(rand() % 360);		// direção da explosão
	explosion.spread    = 180.0f;					// espalhamento em graus
	explosion.lifeTime  = 2.0f;						// tempo de vida em segundos
	explosion.genTime   = 0.000f;					// tempo entre geração de novas partículas
	explosion.percToDim = 0.6f;						// desaparece após 60% da vida
	explosion.minSpeed  = 25.0f;					// velocidade mínima das partículas
	explosion.maxSpeed  = 250.0f;					// velocidade máxima das partículas
	explosion.r = rand() % 101 * 0.01f;				// cor da partícula entre 0 e 1
	explosion.g = rand() % 101 * 0.01f;				// cor da partícula entre 0 e 1
	explosion.b = rand() % 101 * 0.01f;				// cor da partícula entre 0 e 1
	explosion.a = 1.0f;								// transparência da partícula

	// cria sistema de partículas
	starsGen = new Particles(explosion);

	// gera 50 partículas na posição do mouse
	starsGen->Generate(window->MouseX(), window->MouseY(), 50);
	type = FIREWORKS;
}

// ---------------------------------------------------------------------------------

Fireworks::~Fireworks()
{
	delete starsGen;
}

// -------------------------------------------------------------------------------

void Fireworks::Update()
{
	// atualiza posição de cada partícula
	starsGen->Update(gameTime);

	// remove da cena quando todas as partículas estão inativas
	if (starsGen->Inactive())
		Refinery::scene->Delete();
}

// -------------------------------------------------------------------------------