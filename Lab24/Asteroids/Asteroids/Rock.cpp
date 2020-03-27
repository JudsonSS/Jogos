/**********************************************************************************
// Rock (Código Fonte)
//
// Criação:		18 Mar 2013
// Atualização:	25 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Rocha espacial
//
**********************************************************************************/

#include "Rock.h"
#include "Debris.h"
#include "Explosion.h"
#include "Asteroids.h"


// ---------------------------------------------------------------------------------
// inicialização de membros estáticos

TileSet * Rock::tile = nullptr;
uint      Rock::count = 0;

// ---------------------------------------------------------------------------------

Rock::Rock()
{
	// usa uma única folha de sprites para todas as rochas
	if (!tile)
		tile = new TileSet("Resources/Asteroids.png", 128, 128, 4, 4);

	// usa animação para desenhar rochas da folha
	anim = new Animation(tile, 0.020f, false);

	// define bounding box das rochas
	Point rocksVertex[4][8] =
	{
		{ Point(-11, -45), Point(12, -47), Point(38, -27), Point(46, 12), Point(37, 28), Point(-4, 53), Point(-33, 37), Point(-43, -20) },
		{ Point(-10, -46), Point(41, -34), Point(52, 2), Point(44, 28), Point(18, 47), Point(-24, 47), Point(-44, 32), Point(-39, -12) },
		{ Point(-4, -44), Point(40, -21), Point(43, 20), Point(37, 29), Point(-1, 49), Point(-34, 36), Point(-46, -11), Point(-19, -39) },
		{ Point(-6, -46), Point(13, -42), Point(35, -16), Point(47, 25), Point(30, 42), Point(2, 50), Point(-46, 13), Point(-44, -8) }
	};
	
	// seleciona aleatoriamente uma rocha do tileset
	frame = randFrame(mt);

	// cria bounding box
	bbox = new Poly(rocksVertex[frame], 8);
	
	// move para posição aleatória dentro da tela
	MoveTo(randWidth(mt), randHeight(mt));
	
	// usa uma escala aleatória entre 0.8 e 1.0
	Scale(1.0f - 0.02f * randFactor(mt));

	// define ângulo de rotação e velocidade aleatoriamente 
	rAngle = -0.05f + (0.01f * randFactor(mt));		// -0.05 a +0.05
	speed.magnitude = 5.0f + randFactor(mt);		// 5.0 a 15.0
	speed.angle = randAngle(mt);					// 0 a 359

	// mais uma rocha criada
	count++;

	// tipo do objeto
	type = ROCK;
}

// ---------------------------------------------------------------------------------

Rock::~Rock()
{
	// remove tileset se for a última rocha
	if (--count == 0)
		delete tile;

	delete bbox;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Rock::OnCollision(Object * obj)
{
	if (obj->type == ROCK)
	{
		// colisão entre asteroides
		Rock* rockA = this;
		Rock* rockB = static_cast<Rock*>(obj);

		// ângulo formado pela linha que liga os centros dos objetos
		float angleRA = rockA->speed.Angle(rockA->X(), rockA->Y(), rockB->X(), rockB->Y());
		float angleRB = angleRA + 180.0f;

		// mantém ângulo na faixa de 0 a 359 graus
		if (angleRB > 360)
			angleRB -= 360.0f;

		// vetores gerados no impacto (com 25% de perda)
		Vector impactRA{ angleRA, 0.75f * rockA->speed.magnitude };
		Vector impactRB{ angleRB, 0.75f * rockB->speed.magnitude };

		// adiciona vetor impacto à velocidade das rochas
		rockA->speed.Add(impactRB);
		rockB->speed.Add(impactRA);

		// limita velocidade das rochas
		if (rockB->speed.magnitude > 15.0f)
			rockB->speed.magnitude = 15.0f;

		if (rockA->speed.magnitude > 15.0f)
			rockA->speed.magnitude = 15.0f;
	}
	else
	{
		// colisão de asteroide com míssil ou nave

		// toca som de explosão
		Asteroids::audio->Play(EXPLOSION);
		
		// remove asteroide
		Asteroids::scene->Delete(this, MOVING);
		
		// se colisão ocorreu com um asteroide grande ou médio
		if (scale > 0.5f)
		{
			// remove míssil da cena
			if (obj->type == MISSILE)
			{
				Explosion* explo = new Explosion(obj->x, obj->y);
				Asteroids::scene->Add(explo, STATIC);
				Asteroids::scene->Delete(obj, MOVING);
			}

			// cria dois asteroids
			Rock * rockA = new Rock();
			Rock * rockB = new Rock();
			rockA->MoveTo(x, y);
			rockB->MoveTo(x, y);
			
			// asteroide grande gera dois médios
			if (scale > 0.75f)
			{
				rockB->Scale(0.70f);
				rockA->Scale(0.70f);
			}
			// asteroide médio gera dois pequenos
			else
			{
				rockB->Scale(0.40f);
				rockA->Scale(0.40f);
			}

			// adiciona dois asteroides menores na cena
			Asteroids::scene->Add(rockA, MOVING);
			Asteroids::scene->Add(rockB, MOVING);
		}
		// se colisão ocorreu com um asteroide pequeno
		else
		{
			// remove míssil da cena
			if (obj->type == MISSILE)
			{
				Explosion * explo = new Explosion(x,y);
				Asteroids::scene->Add(explo, STATIC);
				Asteroids::scene->Delete(obj, MOVING);
			}

			// cria explosão na posição do asteroide
			Debris * debris = new Debris(x,y);
			Asteroids::scene->Add(debris, STATIC);

			// se a quantidade de asteroides está baixa
			if (count <= 50)
			{
				// adiciona asteroide grande na cena
				Rock * rock = new Rock();

				// pega tamanho do asteroid pela sua bounding box
				Poly * pol = static_cast<Poly*>(rock->bbox);

				// usa o raio como metade do tamanho do asteroide
				float half = pol->BBox()->Radius();

				// asteroide nasce fora da tela
				rock->MoveTo(randWidth(mt), -half);

				Asteroids::scene->Add(rock, MOVING);
			}
		}
	}	
}

// ---------------------------------------------------------------------------------

void Rock::Update()
{
	// rotaciona rocha pelo fator de rotação
	Rotate(rAngle);

	// move rocha usando o vetor velocidade
	Translate(speed.XCom() * gameTime, -speed.YCom() * gameTime);

	// pega tamanho do asteroid pela sua bounding box
	Poly * pol = static_cast<Poly*>(bbox);

	// usa o raio como metade do tamanho do asteroide
	float half = pol->BBox()->Radius();

	// mantém rocha dentro da tela
	if (x + half < 0)
		MoveTo(float(window->Width()) + half, y);
	if (x - half > window->Width())
		MoveTo(-half, y);
	if (y + half < 0)
		MoveTo(x, float(window->Height()) + half);
	if (y - half > window->Height())
		MoveTo(x, -half);
}

// ---------------------------------------------------------------------------------