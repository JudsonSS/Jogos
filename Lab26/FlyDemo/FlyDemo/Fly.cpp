/**********************************************************************************
// Fly (C�digo Fonte)
// 
// Cria��o:		10 Out 2012
// Atualiza��o:	06 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Simula o v�o aleat�rio de uma mosca
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
	// nova dire��o aleat�ria
	speed.magnitude = magnitude.Rand();
	speed.angle = angle.Rand();

	// tempo aleat�rio
	delay = secs.Rand();

	// inicia medi��o do tempo
	timer.Start();
}

// -------------------------------------------------------------------------------

void Fly::Update()
{
	// deslocamento padr�o
	float delta = 50 * gameTime;

	// muda dire��o da mosca ap�s transcorrer certo tempo 
	if (timer.Elapsed(delay))
		NewDirection();

	// movimenta mosca pelo seu vetor velocidade
	Translate(speed.XCom() * delta, -speed.YCom() * delta);

	// mant�m mosca dentro da tela
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