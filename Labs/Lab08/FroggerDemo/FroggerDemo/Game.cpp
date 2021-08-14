/**********************************************************************************
// Game (Código Fonte)
//
// Criação:     08 Dez 2012
// Atualização: 10 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Uma class abstrata para representar um jogo.
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

Window* & Game::window   = Engine::window;       // ponteiro para a janela
float   & Game::gameTime = Engine::frameTime;    // tempo do último quadro

// -------------------------------------------------------------------------------

Game::Game()
{
}

// -------------------------------------------------------------------------------

Game::~Game()
{
}

// -------------------------------------------------------------------------------

void Game::OnPause()
{
    Sleep(10);
}

// -------------------------------------------------------------------------------