/**********************************************************************************
// Fly (Código Fonte)
// 
// Criação:		10 Out 2012
// Atualização:	06 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Simula o vôo aleatório de uma mosca
//
**********************************************************************************/

#include "Fly.h"
#include "FlyDemo.h"

// ---------------------------------------------------------------------------------

Fly::Fly(Image * img): magnitude(1,4), angle(0,359), secs(0.1f, 0.5f)
{
	sprite = new Sprite(img);
	MoveTo(464, 292);
	ScaleTo(0.5f);
	NewDirection();
	type = FLY;
}

// ---------------------------------------------------------------------------------

Fly::~Fly()
{
	delete sprite;
}

// -------------------------------------------------------------------------------
	
void Fly::NewDirection()
{
	// nova direção aleatória
	speed.magnitude = magnitude.Rand();
	speed.angle = angle.Rand();

	// tempo aleatório
	delay = secs.Rand();

	// inicia medição do tempo
	timer.Start();
}

// -------------------------------------------------------------------------------

void Fly::Update()
{
	// deslocamento padrão
	float delta = 50 * gameTime;

	// muda direção da mosca após transcorrer certo tempo 
	if (timer.Elapsed(delay))
		NewDirection();

	// movimenta mosca pelo seu vetor velocidade
	Translate(speed.XCom() * delta, -speed.YCom() * delta);

	// mantém mosca dentro da tela
	if (x < 0)
	{
		MoveTo(0, y);
		speed.angle = 0;
	}
	if (y < 0)
	{
		MoveTo(x, 0);
		speed.angle = 270;
	}
	if (x >window->Width())
	{
		MoveTo(float(window->Width()), y);
		speed.angle = 180;
	}
	if (y > window->Height())
	{
		MoveTo(x, float(window->Height()));
		speed.angle = 90;
	}
}

// -------------------------------------------------------------------------------