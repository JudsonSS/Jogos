/**********************************************************************************
// Alien (Código Fonte)
// 
// Criação:		25 Mar 2013
// Atualização:	11 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Executa scripts com padrões de movimentação
//
**********************************************************************************/

#include "Alien.h"
#include "Stage.h"
#include "Patterns.h"
#include "Explosion.h"
#include <cmath>

// ---------------------------------------------------------------------------------

Alien::Alien(uint alien, Instruction * vet, int tam, float iniX, float iniY) 
	: angle(-8,8), magnitude(1,8)
{
	// tipo do alien
	type = alien;

	// faz cópia do script 
	script = new Instruction[tam];
	for (int i=0; i < tam; i++)
		script[i] = vet[i];

	// carrega tileset do objeto
	switch (type)
	{
	case ALIEN1: alienSet = new TileSet("Resources/Alien1.png", 26, 20, 2, 2); break;
	case ALIEN2: alienSet = new TileSet("Resources/Alien2.png", 26, 20, 2, 2); break;
	case ALIEN3: alienSet = new TileSet("Resources/Alien3.png", 28, 28, 2, 2); break;
	case ALIEN4: alienSet = new TileSet("Resources/Alien4.png", 28, 28, 2, 2); break;
	}
	anim = new Animation(alienSet, 0.500, true);
	
	// configuração inicial do objeto
	bbox = new Rect(-13, -10, 13, 10);
	speed = { 0.0f, 0.0f };
	MoveTo(iniX, iniY);

	// inicia execução do script
	index = 0;
	end = tam - 1;
	duration = script[index].duration;
	timer.Start();

	// mais um inimigo
	++Stage::enemies;
}

// ---------------------------------------------------------------------------------

Alien::~Alien()
{
	delete [] script;
	delete alienSet;
	delete anim;
	delete bbox;

	// menos um inimigo
	--Stage::enemies;
}

// ---------------------------------------------------------------------------------

void Alien::OnCollision(Object * obj)
{
	// se colidiu com um míssil
	if (obj->Type() == MISSILE)
	{
		// deleta missíl
		Patterns::scene->Delete(obj, STATIC);

		// toca som de acordo com o alien atingido
		switch (type)
		{
		case ALIEN1: Patterns::audio->Play(ALIEN1); break;
		case ALIEN2: Patterns::audio->Play(ALIEN2); break;
		case ALIEN3: Patterns::audio->Play(ALIEN3); break;
		case ALIEN4: Patterns::audio->Play(ALIEN4); break;
		}

		if (type == ALIEN3)
		{
			// o alien 3 vira o alien 4 ao ser atingido
			delete anim;
			delete alienSet;
			alienSet = new TileSet("Resources/Alien4.png", 28, 28, 2, 2);
			anim = new Animation(alienSet, 0.500, true);
			type = ALIEN4;
		}
		else
		{
			// qualquer outro alien morre com um tiro
			Patterns::scene->Add(new Explosion(x, y), STATIC);
			Patterns::scene->Delete(this, MOVING);			
		}
	}
}

// -------------------------------------------------------------------------------

void Alien::Update()
{
	// deslocamento padrão
	float delta = 50 * gameTime;

	// atualiza animações
	anim->NextFrame();

	// passa para próxima instrução do script
	if (script[index].instruction == MOVETO || script[index].instruction == SLIDETO)
	{
		float targetX = script[index].angle;
		float targetY = script[index].magnitude;

		if (abs(x - targetX) < 2 && abs(y - targetY) < 2)
		{
			MoveTo(targetX, targetY);
			index = (index == end ? index : ++index);
			duration = script[index].duration;
			timer.Start();
		}
	}
	else
	{
		if (timer.Elapsed(duration))
		{
			index = (index == end ? index : ++index);
			duration = script[index].duration;
			timer.Start();
		}
	}
	
	// vetor alvo para a instrução TURN
	Vector target;

	// realiza salto antes de qualquer instrução
	if (script[index].instruction == JUMP)
	{
		index = int(script[index].angle);
		duration = script[index].duration;
		timer.Start();
	}

	// interpretador do script
	switch (script[index].instruction)
	{
	case MOVE:
		speed.angle = script[index].angle;
		speed.magnitude = script[index].magnitude;
		RotateTo(-speed.angle + 90);
		break;

	case MOVETO:
		speed.angle = speed.Angle(x, y, script[index].angle, script[index].magnitude);
		speed.magnitude = script[index].duration;
		RotateTo(-speed.angle + 90);
		break;

	case SLIDE:
		speed.angle = script[index].angle;
		speed.magnitude = script[index].magnitude;
		break;

	case SLIDETO:
		speed.angle = speed.Angle(x, y, script[index].angle, script[index].magnitude);
		speed.magnitude = script[index].duration;
		break;

	case TURN:
		target.angle = script[index].angle;
		target.magnitude = script[index].magnitude * delta;
		speed.Add(target);
		RotateTo(-speed.angle + 90);
		break;

	case ROTATE:
		speed.angle += script[index].angle * delta;
		speed.magnitude = script[index].magnitude;
		Rotate(-script[index].angle * delta);
		break;

	case RANDOM:
		speed.angle += angle.Rand();
		speed.magnitude = magnitude.Rand();
		RotateTo(-speed.angle + 90);
		break;
	}

	// desloca objeto pelo seu vetor velocidade
	Translate(speed.XCom() * delta, -speed.YCom() * delta);
}

// -------------------------------------------------------------------------------