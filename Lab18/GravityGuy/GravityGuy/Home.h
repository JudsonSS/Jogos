/**********************************************************************************
// Home (Arquivo de Cabeçalho)
// 
// Criação:		14 Fev 2013
// Atualização:	04 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Tela de abertura do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_HOME_H_
#define _GRAVITYGUY_HOME_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
	Sprite * backg;					// background
	TileSet * tileset;				// tileset da animação
	Animation * anim;				// animação do menu

public:
	void Init();					// inicia nível
	void Update();					// atualiza lógica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza nível
};

// -----------------------------------------------------------------------------

#endif