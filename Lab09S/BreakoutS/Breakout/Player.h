/**********************************************************************************
// Player (Arquivo de Cabe�alho)
// 
// Cria��o:		22 Dez 2012
// Atualiza��o: 28 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Player do jogo Breakout
//
**********************************************************************************/

#ifndef _BREAKOUT_PLAYER_H_
#define _BREAKOUT_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"			// tipos espec�ficos da engine
#include "Object.h"			// interface de Object
#include "Sprite.h"			// interface de Sprites

// ---------------------------------------------------------------------------------
// Constantes Globais

enum PLAYERSTATE {PLAYING, STOPED};	

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
	Sprite * sprite;				
	float vel;						

public:
	uint state;

	Player();
	~Player();

	void Update();
	void Draw();
};

// ---------------------------------------------------------------------------------

inline void Player::Draw()
{ sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif