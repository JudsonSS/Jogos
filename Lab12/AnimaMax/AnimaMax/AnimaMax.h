/**********************************************************************************
// AnimaMax (Arquivo de Cabeçalho)
//
// Criação:		10 Abr 2012
// Atualização: 06 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Exemplo de uso da classe Animation
//
**********************************************************************************/

#ifndef _ANIMAMAX_H_
#define _ANIMAMAX_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Sprite.h"
#include "TileSet.h"

// ------------------------------------------------------------------------------

class AnimaMax : public Game
{
private:
	Sprite * bar = nullptr;			// instruções
	Sprite * backg = nullptr;		// sprite de fundo
	TileSet * tileset = nullptr;	// folha de sprites da explosão
	bool keyCtrl = false;			// controla pressionamento de teclas	

public:
	static Scene * scene;			// gerenciador de cena

	void Init();					// inicializa jogo
	void Update();					// atualiza lógica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif