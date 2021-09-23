/**********************************************************************************
// Trials (Arquivo de Cabeçalho)
// 
// Criação:     14 Mai 2012
// Atualização: 22 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de interface com menus
//
**********************************************************************************/

#ifndef _TRIALS_H_
#define _TRIALS_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Mouse.h"
#include "Item.h"
#include "Sprite.h"
#include "Scene.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

enum MenuID {SINGLE, MULTI, TRACKS, LEADERBOARD, OPTIONS, EXIT};

enum Music  {EVOLUTION};

// ------------------------------------------------------------------------------

class Trials : public Game
{
private:
    static const int MaxItens = 6;    // número de itens do menu

    Scene  * scene = nullptr;         // cena do jogo
    Audio  * audio = nullptr;         // sistema de áudio
    Sprite * backg = nullptr;         // plano de fundo
    Mouse  * mouse = nullptr;         // objeto mouse
    
    Item * menu[MaxItens] = { 0 };    // itens do menu
    
    bool viewBBox = false;            // visualiza bounding box
    
public:
    void Init();                      // inicialização
    void Update();                    // atualização
    void Draw();                      // desenho
    void Finalize();                  // finalização
};

// ---------------------------------------------------------------------------------

#endif