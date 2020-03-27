/**********************************************************************************
// Game (Código Fonte)
//
// Criação:		08 Dez 2012
// Atualização:	31 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Uma classe abstrata para representar um jogo.
//
//              Para criar um jogo o programador deve criar uma classe derivada
//              de Game e sobrescrever os métodos Init, Update, Draw e Finalize.
//              Para rodar o jogo, deve-se passar o objeto Game para o método
//              Start() de um objeto Engine.
//
**********************************************************************************/

#include "Game.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Window * Game::window   = nullptr;					// ponteiro para a janela
float &  Game::gameTime = Engine::frameTime;		// tempo do último quadro

// -------------------------------------------------------------------------------

Game::Game()
{
	if (!window)
	{
		// assume que a instância da engine é  
		// criada antes da instância do jogo
		window = Engine::window;
	}
}

// -------------------------------------------------------------------------------

Game::~Game()
{
}

// -------------------------------------------------------------------------------