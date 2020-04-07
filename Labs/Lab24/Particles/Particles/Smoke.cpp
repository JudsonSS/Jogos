/**********************************************************************************
// Smoke (Código Fonte)
// 
// Criação:		17 Mar 2013
// Atualização:	31 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Efeito de fumaça usando sistema de partículas
//
**********************************************************************************/

#include "Smoke.h"
#include "Refinery.h"

// ---------------------------------------------------------------------------------

Smoke::Smoke(float pX, float pY, float angle, bool night)
{
	// configura emissor de partículas
	Emitter smoke;
	smoke.imgFile   = "Resources/Smoke.png";	// arquivo de imagem
	smoke.angle     = angle;					// direção da fumaça
	smoke.spread    = 15;						// espalhamento em graus
	smoke.lifeTime  = 1.0f;						// tempo de vida em segundos
	smoke.genTime   = 0.010f;					// tempo entre geração de novas partículas
	smoke.percToDim = 0.6f;						// desaparece após 60% da vida
	smoke.minSpeed  = 75.0f;					// velocidade mínima das partículas
	smoke.maxSpeed  = 100.0f;					// velocidade máxima das partículas

	// cor da partícula depende da iluminação
	if (night)
	{
		smoke.r = 0.2f;							// cor da partícula
		smoke.g = 0.2f;							// cor da partícula
		smoke.b = 0.2f;							// cor da partícula
		smoke.a = 1.0f;							// cor da partícula
	}
	else
	{
		smoke.r = 1.0f;							// cor da partícula
		smoke.g = 1.0f;							// cor da partícula
		smoke.b = 1.0f;							// cor da partícula
		smoke.a = 1.0f;							// cor da partícula
	}

	// cria sistema de partículas
	smokeGen = new Particles(smoke);
	MoveTo(pX, pY);
	stop = false;
	type = SMOKE;
}

// ---------------------------------------------------------------------------------

Smoke::~Smoke()
{
	delete smokeGen;
}

// -------------------------------------------------------------------------------

void Smoke::TurnOff()
{
	stop = true;
}

// -------------------------------------------------------------------------------

void Smoke::Update()
{
	if (stop)
	{
		if (smokeGen->Inactive())
			Refinery::scene->Delete();
	}
	else
	{
		smokeGen->Generate(x, y);
	}

	smokeGen->Update(gameTime);
}

// -------------------------------------------------------------------------------
