/**********************************************************************************
// Sound Distance (Arquivo de Cabeçalho)
// 
// Criação:     14 Out 2011
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Ajusta volume pela distância do som
//
**********************************************************************************/

#ifndef _SOUNDDIST_H_
#define _SOUNDDIST_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Font.h"
#include "Audio.h"
#include "Scene.h"
#include "Sprite.h"
#include "Player.h"
#include "Bar.h"
#include "Resources.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

enum Sounds {PULSE, EXPLOSION};

// ------------------------------------------------------------------------------

class SoundDist : public Game
{
private:
    Sprite * backg = nullptr;       // background do jogo

    bool keyCtrl  = false;          // controle de teclas    
    bool viewBBox = false;          // visualiza bounding box

public:
    static Audio * audio;           // sistema de áudio    
    static Scene * scene;           // cema do jogo

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

// ------------------------------------------------------------------------------

#endif