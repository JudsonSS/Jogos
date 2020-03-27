/**********************************************************************************
// Particles (Código Fonte)
// 
// Criação:		07 Out 2012
// Atualização:	30 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define um sistema de partículas
//
**********************************************************************************/

#include "Particles.h"
#include "Geometry.h"
#include <cmath>

// ---------------------------------------------------------------------------------

Particles::Particles(const Emitter & desc) : emitter(desc)
{
	sprite = new Sprite(desc.imgFile);
	timer.Start();
}

// ---------------------------------------------------------------------------------

Particles::~Particles()
{
	delete sprite;
	for (const auto & p : particles)
		delete p;
}

// ---------------------------------------------------------------------------------

void Particles::Build(float posX, float posY)
{
	// cria partícula
	Particle * p = new Particle();

	// ajusta posição
	p->x = posX;
	p->y = posY;
	
	// pega um ângulo aleatório a partir do ângulo base e espalhamento
	float angle = emitter.angle + randSpread(mt);

	// mantém ângulo na faixa 0 a 359 graus
	if (angle > 360)
		angle -= 360;
	else 
		if (angle < 0)
		angle += 360;
	
	// ajusta vetor velocidade da partícula
	p->speed.angle = angle;	
	p->speed.magnitude = randSpeed(mt);
	p->timeStamp = timer.Stamp();

	// insere partícula no vetor de partículas
	particles.push_back(p);
}

// ---------------------------------------------------------------------------------

void Particles::Generate(float x, float y, int amount)
{
	if (amount == 1)
	{
		// gera uma partícula por vez
		if (timer.Elapsed(emitter.genTime)) 
		{
			Build(x, y);
			timer.Start();
		}
	} 
	else 
	{	
		// gera todas as partículas de uma vez
		for (int i = 0; i < amount; ++i)
			Build(x, y);
	}
}

// ---------------------------------------------------------------------------------

void Particles::Update(float delta)
{
	float lifePercent = 0;
	float timeElapsed = 0;

	// percorre o vetor de partículas
	auto i = particles.begin();
	while (i != particles.end())
	{
		// para cada partícula
		Particle * p = *i;

		// atualiza a posição da partícula usando seu vetor velocidade
		p->x += p->speed.XCom() * delta;
		p->y -= p->speed.YCom() * delta;
		
		// calcula o percentual de vida da partícula
		timeElapsed = timer.Elapsed(p->timeStamp);
		lifePercent = timeElapsed/emitter.lifeTime;

		// torna a partícula transparente com o passar do tempo
		if (lifePercent > emitter.percToDim)
		{
			// transparência cresce cubicamente com o tempo de vida
			emitter.a = 1.0f - pow(lifePercent, 3);
		}

		if (timeElapsed > emitter.lifeTime)
		{
			// remove a partícula sem vida
			delete p;
			i = particles.erase(i);
		}
		else
		{
			// passa para próxima partícula
			++i;
		}
	}
}

// ---------------------------------------------------------------------------------

void Particles::Draw(float z, float factor)
{
	float lifePercent = 0.0f;
	float timeElapsed = 0.0f;
	
	// para cada partícula do vetor
	for (Particle * p : particles)
	{
		// calcula o percentual de vida da partícula
		timeElapsed = timer.Elapsed(p->timeStamp);
		lifePercent = timeElapsed/emitter.lifeTime;

		// escala cresce quadraticamente com o tempo de vida
		float scale = 1.0f + pow(lifePercent, 2) * factor;

		// desenha partícula
		sprite->Draw(p->x, p->y, z, scale, -p->speed.angle, Color(emitter.r, emitter.g, emitter.b, emitter.a));
	}	
}

// ---------------------------------------------------------------------------------
