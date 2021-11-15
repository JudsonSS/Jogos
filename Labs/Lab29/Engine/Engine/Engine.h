/**********************************************************************************
// Engine (Arquivo de Cabeçalho)
//
// Criação:     15 Mai 2014
// Atualização: 25 Ago 2021
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

#ifdef ENGINE_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// ---------------------------------------------------------------------------------

#include "Game.h"                        // implementação do jogo
#include "Window.h"                      // janela do jogo
#include "Graphics.h"                    // hardware gráfico
#include "Renderer.h"                    // renderizador de sprites
#include "Timer.h"                       // medidor de tempo

// ---------------------------------------------------------------------------------

class DLL Engine
{
private:
    static Timer timer;                  // medidor de tempo
    static bool paused;                  // estado do jogo

    float FrameTime();                   // calcula o tempo do quadro
    int   Loop();                        // inicia execução do jogo

public:
    static Game     * game;              // jogo a ser executado
    static Window   * window;            // janela do jogo
    static Graphics * graphics;          // dispositivo gráfico
    static Renderer * renderer;          // renderizador de sprites
    static float      frameTime;         // tempo do quadro atual

    Engine();                            // construtor
    ~Engine();                           // destrutor

    int Start(Game* level);              // inicia a execução do jogo
    
    static void Pause();                 // pausa o jogo
    static void Resume();                // reinicia o jogo

    template<class T>
    static void Next()                   // muda para próximo nível do jogo
    {
        if (game)
        {
            game->Finalize();
            delete game;
            game = new T();
            game->Init();
        }
    };
};

// ---------------------------------------------------------------------------------

#endif