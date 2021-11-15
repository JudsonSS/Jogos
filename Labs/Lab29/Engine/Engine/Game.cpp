/**********************************************************************************
// Game (Código Fonte)
//
// Criação:     08 Dez 2012
// Atualização: 01 Nov 2021
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

Canvas    Game::world    = { 0, 0, 0, 0 };       // área do jogo
Window* & Game::window   = Engine::window;       // ponteiro para a janela
Game*   & Game::game     = Engine::game;         // ponteiro para o jogo
float   & Game::gameTime = Engine::frameTime;    // tempo do último quadro

// -------------------------------------------------------------------------------

Game::Game()
{
    // o tamanho do jogo é o tamanho da janela
    Size(window->Width(), window->Height());

    // a área visível é a mesma da janela
    viewport = { 0, 0, window->Width(), window->Height() };
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

void Game::Size(float width, float height)
{
    world.width = width;
    world.height = height;
    world.centerX = width / 2;
    world.centerY = height / 2;
}

// -------------------------------------------------------------------------------