/**********************************************************************************
// D3DBreakout (Arquivo de Cabeçalho)
//
// Criação:     26 Mar 2012
// Atualização: 18 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exercício sobre uso da classe Scene para gerenciar objetos
//
**********************************************************************************/

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

class Breakout : public Game
{
private:
    Sprite * backg;             // plano de fundo
    Image * tile1;              // bloco verde
    Image * tile2;              // bloco cinza
    Image * tile3;              // bloco vermelho
    Image * tile4;              // bloco roxo
    Image * tile5;              // bloco amarelo

public:
    static Scene * scene;       // cena do jogo

    void Init();                // inicialização
    void Update();              // atualização
    void Draw();                // desenho
    void Finalize();            // finalização
};

// ------------------------------------------------------------------------------
