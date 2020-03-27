/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:		25 Mar 2013
// Atualização:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define a classe jogador
//
**********************************************************************************/

#ifndef _PATTERNS_PLAYER_H_
#define _PATTERNS_PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Object.h"						// objetos do jogo
#include "Image.h"						// carregamento de imagens
#include "Sprite.h"						// desenho de sprites
#include "TileSet.h"					// folha de quadros

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
	Image * missile;					// imagem do míssil
	Sprite * sprite;					// sprite do objeto

public:
	static TileSet * exploSet;			// tileset da explosão

	Player();							// construtor
	~Player();							// destrutor

	void Update();						// atualiza estado do objeto
	void Draw();						// desenha objeto
}; 

// ---------------------------------------------------------------------------------

inline void Player::Draw()
{ sprite->Draw(x, y, Layer::FRONT); }

// ---------------------------------------------------------------------------------

#endif