/**********************************************************************************
// Hud (Arquivo de Cabeçalho)
//
// Criação:     02 Ago 2019
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Heads Up Display
//
**********************************************************************************/

#ifndef _WAVESDEMO_HUD_H_
#define _WAVESDEMO_HUD_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Font.h"
#include <sstream>
using std::stringstream;

// --------------------------------------------------------------------------------

class Hud : public Object
{
private:
    Font * font;                        // fonte para exibição normal
    Font * bold;                        // fonte para exibição negrito
    Sprite * infoBox;                   // área de informações do jogo
    Sprite * keyMap;                    // área para teclas de comando
    stringstream text;                  // texto temporário

public:
    static uint missiles;               // número de mísseis na tela
    static uint enemies;                // número de inimigos laranja
    static uint waves;                  // número de ondas de inimigos

    Hud();                              // construtor
    ~Hud();                             // destrutor

    void Update();                      // atualização
    void Draw();                        // desenho
};

// ------------------------------------------------------------------------------

#endif

