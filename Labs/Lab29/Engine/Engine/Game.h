/**********************************************************************************
// Game (Arquivo de Cabeçalho)
//
// Criação:     08 Dez 2012
// Atualização: 01 Nov 2021
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

#ifdef ENGINE_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// ---------------------------------------------------------------------------------

#include "Types.h"
#include "Window.h"

// ---------------------------------------------------------------------------------

class DLL Game
{
private:
    static Canvas world;                            // área do jogo

    // Membros protegidos são privados para o mundo externo mas
    // públicos para as classes derivadas, ou seja, as classes
    // derivadas de Game serão capazes de acessar estes membros.

protected:
    static Window* & window;                        // janela do jogo
    static Game*   & game;                          // jogo em execução
    static float   & gameTime;                      // tempo do último quadro

public:
    ViewPort viewport;                              // área visível do jogo
    
    Game();                                         // construtor 

    // Métodos virtuais garantem que uma chamada através de um
    // ponteiro para a classe base, vai invocar o método da classe
    // derivada, se ele existir, em vez de chamar sempre o método 
    // da classe base.

    virtual ~Game();                                // destrutor
    virtual void OnPause();                         // pausa do jogo

    static void Size(float width, float height);    // define o tamanho do jogo
    static float Width();                           // retorna a largura do jogo
    static float Height();                          // retorna a altura do jogo
    static float CenterX();                         // retorna o centro do jogo no eixo x
    static float CenterY();                         // retorna o centro do jogo no eixo y

    // Estes métodos são puramente virtuais, isto é, devem ser 
    // implementados em todas as classes derivas de Game.

    virtual void Init() = 0;                        // inicialização do jogo
    virtual void Update() = 0;                      // atualização do jogo
    virtual void Draw() = 0;                        // desenho da cena
    virtual void Finalize() = 0;                    // finalização do jogo
};

// ---------------------------------------------------------------------------------

inline float Game::Width()
{ return world.width; }

inline float Game::Height()
{ return world.height; }

inline float Game::CenterX()
{ return world.centerX; }

inline float Game::CenterY()
{ return world.centerY; }

// ---------------------------------------------------------------------------------

#endif