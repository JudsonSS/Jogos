/**********************************************************************************
// Engine (Arquivo de Cabeçalho)
//
// Criação:     15 Mai 2014
// Atualização: 08 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   A função da Engine é rodar jogos criados a partir da classe
//              abstrata Game. Todo jogo deve ser uma classe derivada de Game
//              e portanto deve implementar as funções membro Init, Update, Draw
//              e Finalize, que serão chamadas pelo motor em um laço de tempo real.
//              Para usar a classe Engine, o programador deve criar uma instância
//              e chamar o método Start(), passando um objeto derivado de Game.
//
**********************************************************************************/

#ifndef _PROGJOGOS_ENGINE_H_
#define _PROGJOGOS_ENGINE_H_

// ---------------------------------------------------------------------------------

#include "Game.h"                      // implementação do jogo
#include "Window.h"                    // janela do jogo
#include "Graphics.h"                  // hardware gráfico

// ---------------------------------------------------------------------------------

class Engine
{
private:
    int Loop();                        // inicia laço principal do jogo

public:
    static Game     * game;            // jogo a ser executado
    static Window   * window;          // janela do jogo
    static Graphics * graphics;        // dispositivo gráfico

    Engine();                          // construtor
    ~Engine();                         // destrutor

    int Start(Game* level);            // inicia a execução do jogo
};

// ---------------------------------------------------------------------------------

#endif