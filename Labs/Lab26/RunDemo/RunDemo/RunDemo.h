/**********************************************************************************
// RunDemo (Arquivo de Cabeçalho)
// 
// Criação:     23 Out 2012
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Demonstração da fuga suavizada
//
**********************************************************************************/

#ifndef _RUNDEMO_H_
#define _RUNDEMO_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Sprite.h"
#include "Player.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, GREEN, WALLHIT };

// ------------------------------------------------------------------------------

enum SoundIds { THEME, FIRE, EXPLODE, HITWALL, SPAWN };

// ------------------------------------------------------------------------------

class RunDemo : public Game
{
private:
    Sprite * backg = nullptr;       // pano de fundo
    Hud * hud = nullptr;            // heads up display    
    bool viewBBox = false;          // bouding box visível

public:
    static Audio * audio;           // sitema de áudio
    static Scene * scene;           // cena do jogo
    static Player* player;          // ponteiro para o jogador

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif