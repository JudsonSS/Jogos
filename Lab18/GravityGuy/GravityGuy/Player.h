/**********************************************************************************
// Player (Arquivo de Cabe�alho)
// 
// Cria��o:		20 Abr 2012
// Atualiza��o:	04 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Define uma classe para o jogador 
//
**********************************************************************************/

#ifndef _GRAVITYGUY_PLAYER_H_
#define _GRAVITYGUY_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"						// tipos espec�ficos da engine
#include "Object.h"						// interface de Object
#include "Animation.h"					// anima��o de sprites

// ------------------------------------------------------------------------------

enum Gravity {NORMAL,INVERTED};			// tipo da gravidade

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
	TileSet   * tileset;				// folha de sprites do personagem
	Animation * anim;					// anima��o do personagem
	uint      gravity;					// gravidade atuando sobre o jogador
	
public:
	Player();							// construtor
	~Player();							// destrutor

	float Bottom();						// coordenadas da base
	float Top();						// coordenadas do topo

	void OnCollision(Object * obj);		// resolu��o da colis�o
	void Update();						// atualiza��o do objeto
	void Draw();						// desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline float Player::Bottom()
{ return y + tileset->Height()/2; }

inline float Player::Top()
{ return y - tileset->Height()/2; }

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif