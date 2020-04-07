/**********************************************************************************
// Orange (Código Fonte)
// 
// Criação:		05 Ago 2019
// Atualização:	05 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Objeto faz movimento retilíneo
//
**********************************************************************************/

#include "GeoWars.h"
#include "Orange.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Orange::Orange(Player * p)
{
	player = p;
	sprite = new Sprite("Resources/Orange.png");
	bbox   = new Circle(20.0f);
	speed  = new Vector(0, 2.0f);

	// ajusta ângulo do vetor na direção do jogador
	speed->angle = speed->Angle(x, y, player->X(), player->Y());
	RotateTo(-speed->angle);
	
	// move para uma posição aleatória (canto superior esquerdo)
	FloatRand posX{ 100, 150 };
	FloatRand posY{ 100, 150 };
	MoveTo(posX.Rand(), posY.Rand());

	multiplier = 70.0f;
	type = ORANGE;

	// configuração do emissor de partículas
	Emitter emitter;
	emitter.imgFile = "Resources/Star.png";		// arquivo de imagem
	emitter.angle = speed->angle + 180;			// ângulo base do emissor
	emitter.spread = 5;						// espalhamento em graus
	emitter.lifeTime = 0.2f;					// tempo de vida em segundos
	emitter.genTime = 0.010f;					// tempo entre geração de novas partículas
	emitter.percToDim = 0.7f;					// desaparece após 60% da vida
	emitter.minSpeed = 50.0f;					// velocidade mínima das partículas
	emitter.maxSpeed = 100.0f;					// velocidade máxima das partículas
	emitter.r = 1.0f;							// componente Red da partícula 
	emitter.g = 0.5;							// componente Green da partícula 
	emitter.b = 0.0f;							// componente Blue da partícula 
	emitter.a = 1.0f;							// transparência da partícula

	// cria sistema de partículas
	tail = new Particles(emitter);
}

// ---------------------------------------------------------------------------------

Orange::~Orange()
{
	delete sprite;
	delete speed;
	delete bbox;
	delete tail;
}

// -------------------------------------------------------------------------------

void Orange::OnCollision(Object * obj)
{
	if (obj->Type() == MISSILE)
		GeoWars::scene->Delete(this, MOVING);
}

// -------------------------------------------------------------------------------

void Orange::Update()
{
	// movimenta objeto pelo seu vetor velocidade
	Translate(speed->XCom() * multiplier * gameTime, -speed->YCom() * multiplier * gameTime);

	// ajusta ângulo do vetor na direção do jogador
	if (x < 100 || y < 100 || x > game->Width() - 100 || y > game->Height() - 100)
	{
		multiplier = 200;
		speed->angle = speed->Angle(x, y, player->X(), player->Y());
		RotateTo(-speed->angle);
	}

	// atualiza calda da nave
	tail->Generator().angle = speed->angle + 180;
	tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
	tail->Update(gameTime);
}

// ---------------------------------------------------------------------------------

void Orange::Draw()
{
	sprite->Draw(x, y, Layer::MIDBACK, scale, rotation);
	tail->Draw(Layer::MIDBACK, 1.0f);
}

// -------------------------------------------------------------------------------