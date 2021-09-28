/**********************************************************************************
// Level1 (Arquivo de Cabeçalho)
// 
// Criação:     14 Fev 2013
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nível 1 do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_LEVEL1_H_
#define _GRAVITYGUY_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Background.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo animado

public:
    static Scene* scene;           // cena do nível

    void Init();                    // inicialização do nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finalização do nível
};

// -----------------------------------------------------------------------------

#endif