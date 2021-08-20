/**********************************************************************************
// Breakout (Arquivo de Cabeçalho)
//
// Criação:     26 Mar 2012
// Atualização: 20 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Uso da classe Scene para gerenciar objetos e tratar colisão
//
**********************************************************************************/

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Resources.h"

// ------------------------------------------------------------------------------
// Tipos dos objetos do jogo

enum ObjTypes
{
    PLAYER,                             // jogador
    BALL,                               // bola
    BLOCK                               // bloco
};

// ------------------------------------------------------------------------------

class Breakout : public Game
{
private:
    Sprite * backg = nullptr;           // plano de fundo
    Image * tile1  = nullptr;           // bloco verde
    Image * tile2  = nullptr;           // bloco cinza
    Image * tile3  = nullptr;           // bloco vermelho
    Image * tile4  = nullptr;           // bloco roxo
    Image * tile5  = nullptr;           // bloco amarelo

    bool viewScene = true;              // visualiza sprites da cena
    bool viewBBox  = false;             // visualiza bounding box
    bool ctrlKeyS  = true;              // controla pressionamento da tecla S
    bool ctrlKeyB  = true;              // controla pressionamento da tecla B

public:
    static Scene * scene;               // cena do jogo

    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ------------------------------------------------------------------------------
