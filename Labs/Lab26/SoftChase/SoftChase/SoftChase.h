/**********************************************************************************
// SoftChase (Arquivo de Cabeçalho)
// 
// Criação:     23 Out 2012
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Demonstração da perseguição suavizada
//
**********************************************************************************/

#ifndef _SOFTCHASE_H_
#define _SOFTCHASE_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Sprite.h"
#include "Player.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, BLUE, WALLHIT };

// ------------------------------------------------------------------------------

enum SoundIds { THEME, FIRE, EXPLODE, HITWALL, SPAWN };

// ------------------------------------------------------------------------------

class SoftChase : public Game
{
private:
    Sprite * backg = nullptr;       // pano de fundo
    Hud * hud = nullptr;            // heads up display    
    bool viewBBox = false;          // ativação das bouding boxes

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