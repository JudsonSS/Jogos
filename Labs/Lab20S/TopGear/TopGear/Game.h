/**********************************************************************************
// Game (Arquivo de Cabeçalho)
//
// Criação:     08 Dez 2012
// Atualização: 10 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Uma classe abstrata para representar um jogo.
//
//              Para criar um jogo o programador deve criar uma classe derivada
//              de Game e sobrescrever os métodos Init, Update, Draw e Finalize.
//              Para rodar o jogo, deve-se passar o objeto Game para o método
//              Start() de um objeto Engine.
//
**********************************************************************************/

#ifndef _PROGJOGOS_GAME_H_
#define _PROGJOGOS_GAME_H_

// ---------------------------------------------------------------------------------

#include "Window.h"

// ---------------------------------------------------------------------------------

class Game
{
    // Membros protegidos são privados para o mundo externo mas
    // públicos para as classes derivadas, ou seja, as classes
    // derivadas de Game serão capazes de acessar estes membros.
protected:
    static Window* & window;                    // janela do jogo
    static float   & gameTime;                  // tempo do último quadro

public:
    Game();                                     // construtor
    virtual ~Game();                            // destrutor
    
    // Métodos que podem ser sobrescritos para implementar 
    // funcionalidade específica para o jogo. Eles já possuem
    // uma implementação padrão.

    virtual void OnPause();                     // pausa do jogo

    // Estes métodos são puramente virtuais, isto é, devem ser 
    // implementados em todas as classes derivas de Game.

    virtual void Init() = 0;                    // inicialização do jogo
    virtual void Update() = 0;                  // atualização do jogo
    virtual void Draw() = 0;                    // desenho da cena
    virtual void Finalize() = 0;                // finalização do jogo
};

// ---------------------------------------------------------------------------------

#endif