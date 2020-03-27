/**********************************************************************************
// Game (C�digo Fonte)
//
// Cria��o:		08 Dez 2012
// Atualiza��o:	24 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Uma classe abstrata para representar um jogo.
//
//              Para criar um jogo o programador deve criar uma classe derivada
//              de Game e sobrescrever os m�todos Init, Update, Draw e Finalize.
//              Para rodar o jogo, deve-se passar o objeto Game para o m�todo
//              Start() de um objeto Engine.
//
**********************************************************************************/

#include "Game.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Window * Game::window = nullptr;				// ponteiro para a janela
float & Game::gameTime = Engine::frameTime;		// tempo do �ltimo quadro

// -------------------------------------------------------------------------------

Game::Game()
{
	if (!window)
	{
		// assume que a inst�ncia da engine �  
		// criada antes da inst�ncia do jogo
		window = Engine::window;
	}
}

// -------------------------------------------------------------------------------

Game::~Game()
{
}

// -------------------------------------------------------------------------------