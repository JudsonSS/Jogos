/**********************************************************************************
// GameOver (Arquivo de Cabeçalho)
// 
// Criação:     14 Fev 2013
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Fim do jogo
//              
**********************************************************************************/

#ifndef _GRAVITYGUY_GAMEOVER_H_
#define _GRAVITYGUY_GAMEOVER_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class GameOver : public Game
{
private:
    Sprite * title = nullptr;       // tela de fim

public:
    void Init();                    // inicialização do nível
    void Update();                  // lógica da tela de fim
    void Draw();                    // desenho da tela
    void Finalize();                // finalização do nível
};

// ------------------------------------------------------------------------------

#endif