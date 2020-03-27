/**********************************************************************************
// AnimaWalk (Arquivo de Cabeçalho)
//
// Criação:		18 Abr 2012
// Atualização: 11 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Usando a classe Animation para animar um personagem
//
**********************************************************************************/

#ifndef _ANIMAWALK_H_
#define _ANIMAWALK_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Sprite.h"
#include "Lady.h"

// ------------------------------------------------------------------------------

class AnimaWalk : public Game
{
private:
	Sprite * backg = nullptr;		// sprite de fundo
	Lady * lady = nullptr;			// objeto com animação	

public:
	static Scene * scene;			// gerenciador de cena

	void Init();					// inicializa jogo
	void Update();					// atualiza lógica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif