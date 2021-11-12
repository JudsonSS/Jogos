/**********************************************************************************
// BasicAI (Arquivo de Cabeçalho)
// 
// Criação:     23 Out 2012
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Demonstração de todas as IAs
//
**********************************************************************************/

#ifndef _BASICAI_H_
#define _BASICAI_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

enum Ids 
{ 
    PLAYER, MISSILE, WALLHIT, BLUE, GREEN, MAGENTA, ORANGE, 
    THEME, START, FIRE, EXPLODE, HITWALL, EXPLOSION 
};

// ------------------------------------------------------------------------------

class BasicAI : public Game
{
private:
    Background * backg = nullptr;   // pano de fundo
    Hud * hud = nullptr;            // heads up display
    bool viewBBox = false;          // visualização das bouding boxes

public:
    static Player * player;         // ponteiro para o jogador
    static Audio * audio;           // sitema de áudio
    static Scene * scene;           // cena do jogo

    static Image * blue;            // imagem do inimigo azul
    static Image * green;           // imagem do inimigo green
    static Image * magenta;         // imagem do inimigo magenta
    static Image * orange;          // imagem do inimigo orange
    
    static bool viewHUD;            // hud visível

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif