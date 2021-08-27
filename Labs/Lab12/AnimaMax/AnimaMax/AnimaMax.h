/**********************************************************************************
// AnimaMax (Arquivo de Cabeçalho)
//
// Criação:     10 Abr 2012
// Atualização: 27 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de uso da classe Animation
//
**********************************************************************************/

#ifndef _ANIMAMAX_H_
#define _ANIMAMAX_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Sprite.h"
#include "TileSet.h"
#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;

// ------------------------------------------------------------------------------

class AnimaMax : public Game
{
private:
    Sprite * text = nullptr;        // instruções
    Sprite * backg = nullptr;       // sprite de fundo
    TileSet * tileset = nullptr;    // folha de sprites da explosão
    bool keyCtrl = false;           // controla pressionamento de teclas 

    random_device rd;               // gerador não determinístico
    mt19937 mt{ rd() };             // gerador mersenne twister

    // distribuições uniformes nas faixas da largura e altura da janela
    uniform_real_distribution<float> randWidth { 0.0f, window->Width() - 1.0f };
    uniform_real_distribution<float> randHeight{ 0.0f, window->Height() - 1.0f };

public:
    static Scene * scene;           // gerenciador de cena

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif