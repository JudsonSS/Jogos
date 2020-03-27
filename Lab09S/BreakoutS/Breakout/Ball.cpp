/**********************************************************************************
// Ball (Arquivo de Cabeçalho)
// 
// Criação:		22 Dez 2012
// Atualização: 28 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Bola do jogo Breakout
//
**********************************************************************************/

#include "Ball.h"

// ---------------------------------------------------------------------------------

Ball::Ball(Player * pl) : player(pl)
{
	// tamanho do player é 100x20
	sprite  = new Sprite("Resources/Ball.png");
	MoveTo(player->x + 50.0f - sprite->Width()/2.0f, player->y - sprite->Height() - 2.0f, Layer::FRONT);
	velX =  250.0f;
	velY = -250.0f;
}

// ---------------------------------------------------------------------------------

Ball::~Ball()
{
	delete sprite;
}

// ---------------------------------------------------------------------------------

void Ball::Update()
{
	if (player->state == PLAYING)
		Translate(velX * gameTime, velY * gameTime);
	else 
		MoveTo(player->x + 50.0f - sprite->Width() / 2.0f, player->y - sprite->Height() - 2.0f, 0.0f);

	// mantém a bola dentro da tela (tam. da bola: 12x12)
	if (x < 0)
	{
		MoveTo(0.0f, y);
		velX = -velX;
	}
	if (x + sprite->Width() > window->Width())
	{
		MoveTo(float(window->Width() - sprite->Width()), y);
		velX = -velX;
	}
	if (y < 0)
	{
		MoveTo(x, 0.0f);
		velY = -velY;
	}
	if (y + sprite->Height() > window->Height())
	{
		MoveTo(x, float(window->Height() - sprite->Height()));
		velY = -velY;
	}
}

// ---------------------------------------------------------------------------------
