/**********************************************************************************
// Platformer (Arquivo de Cabeçalho)
//
// Criação:     05 Out 2011
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de jogo estilo platforma
//
**********************************************************************************/

#ifndef _PLATFORMER_H_
#define _PLATFORMER_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Platform.h"
#include "Background.h"
#include "Player.h"

// ------------------------------------------------------------------------------

enum { MUSIC, TRANSITION };

// ------------------------------------------------------------------------------

class Platformer : public Game
{
private:
    Player * player = nullptr;      // personagem controlado pelo jogador
    Background * backg = nullptr;   // pano de fundo do jogo

public:
    static Scene * scene;           // gerenciador de cena
    static Audio * audio;           // gerenciador de audio

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif