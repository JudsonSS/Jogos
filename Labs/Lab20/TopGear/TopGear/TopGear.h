/**********************************************************************************
// TopGear (Arquivo de Cabeçalho)
//
// Criação:     11 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Uso da escala em um jogo estilo TopGear
//
**********************************************************************************/

#ifndef _TOPGEAR_H_
#define _TOPGEAR_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

enum SoundIds { MUSIC, ENGINE, COLLISION };

// ------------------------------------------------------------------------------

class TopGear : public Game
{
private:
    Scene * scene = nullptr;            // gerenciador de cena
    Sprite * sky = nullptr;             // desenho do céu
    Sprite * track = nullptr;           // desenho da pista

    bool viewBBox = false;              // visualização da bbox

public:
    static Audio * audio;               // gerenciador de áudio
    static float speed;                 // velocidade do carro

    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ---------------------------------------------------------------------------------

#endif