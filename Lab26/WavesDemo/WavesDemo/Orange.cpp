/**********************************************************************************
// Orange (Código Fonte)
// 
// Criação:		05 Ago 2019
// Atualização:	07 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Objeto faz movimento retilíneo
//
**********************************************************************************/

#include "WavesDemo.h"
#include "Orange.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Orange::Orange(float pX, float pY, float ang)
{
	sprite = new Sprite("Resources/Orange.png");
	bbox   = new Circle(20.0f);

	// ajusta o vetor velocidade
	speed.angle = ang;
	speed.magnitude = 400;
	RotateTo(-speed.angle);
	MoveTo(pX, pY);
	type = ORANGE;

	// configuração do emissor de partículas
	Emitter emitter;
	emitter.imgFile = "Resources/Star.png";		// arquivo de imagem
	emitter.angle = speed.angle + 180;			// ângulo base do emissor
	emitter.spread = 5;							// espalhamento em graus
	emitter.lifeTime = 0.4f;					// tempo de vida em segundos
	emitter.genTime = 0.010f;					// tempo entre geração de novas partículas
	emitter.percToDim = 0.8f;					// desaparece após 60% da vida
	emitter.minSpeed = 100.0f;					// velocidade mínima das partículas
	emitter.maxSpeed = 200.0f;					// velocidade máxima das partículas
	emitter.r = 1.0f;							// componente Red da partícula 
	emitter.g = 0.5;							// componente Green da partícula 
	emitter.b = 0.0f;							// componente Blue da partícula 
	emitter.a = 1.0f;							// transparência da partícula

	// cria sistema de partículas
	tail = new Particles(emitter);

	// incrementa contagem
	++Hud::enemies;
}

// ---------------------------------------------------------------------------------

Orange::~Orange()
{
	delete sprite;
	delete bbox;
	delete tail;

	// decrementa contagem
	--Hud::enemies;
}

// -------------------------------------------------------------------------------

void Orange::OnCollision(Object * obj)
{
	if (obj->Type() == MISSILE)
	{
		WavesDemo::scene->Delete(obj, STATIC);
		WavesDemo::scene->Delete(this, MOVING);
		WavesDemo::audio->Play(EXPLODE);
	}
}

// -------------------------------------------------------------------------------

void Orange::Update()
{
	// movimenta objeto pelo seu vetor velocidade
	Translate(speed.XCom() * gameTime, -speed.YCom() * gameTime);

	// ajusta ângulo do vetor na direção oposta
	if (x < 0 || y < 0 || x > game->Width() || y > game->Height())
	{
		Rotate(180);
		speed.Rotate(180);		
		Translate(speed.XCom() * gameTime, -speed.YCom() * gameTime);
	}

	// atualiza calda da nave
	tail->Generator().angle = speed.angle;
	tail->Generate(x - 10 * cos(speed.Radians()), y + 10 * sin(speed.Radians()));
	tail->Update(gameTime);
}

// ---------------------------------------------------------------------------------

void Orange::Draw()
{
	sprite->Draw(x, y, Layer::MIDBACK, scale, rotation);
	tail->Draw(Layer::MIDBACK, 1.0f);
}

// -------------------------------------------------------------------------------