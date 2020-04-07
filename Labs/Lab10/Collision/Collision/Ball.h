/**********************************************************************************
// Ball (Arquivo de Cabeçalho)
// 
// Criação:		22 Dez 2012
// Atualização:	31 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Bola do jogo Breakout
//
**********************************************************************************/

#ifndef _BREAKOUT_BALL_H_
#define _BREAKOUT_BALL_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"			// tipos específicos da engine
#include "Object.h"			// interface de Object
#include "Sprite.h"			// interface de Sprites
#include "Player.h"			// jogador do Breakout

// ---------------------------------------------------------------------------------

class Ball : public Object
{
private:
	Player * player;		// ponteiro para jogador
	Sprite * sprite;		// sprite do player

public:
	float velX;				// velocidade horizontal
	float velY;				// velocidade vertical	

	Ball(Player * p);
	~Ball();

	void OnCollision(Object * obj);
	void Update();
	void Draw();
};

// ---------------------------------------------------------------------------------

inline void Ball::Draw()
{ sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif