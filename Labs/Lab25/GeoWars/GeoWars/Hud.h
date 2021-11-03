/**********************************************************************************
// Hud (Arquivo de Cabeçalho)
//
// Criação:     02 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Heads Up Display
//
**********************************************************************************/

#ifndef _GEOWARS_HUD_H_
#define _GEOWARS_HUD_H_

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
    Font * font = nullptr;              // fonte para exibição normal
    Font * bold = nullptr;              // fonte para exibição negrito
    Sprite * infoBox = nullptr;         // área de informações do jogo
    Sprite * keyMap = nullptr;          // área para teclas de comando
    stringstream text;                  // texto temporário

public:
    Hud();                              // construtor
    ~Hud();                             // destrutor

    void Update();                      // atualização
    void Draw();                        // desenho
};

// ------------------------------------------------------------------------------

#endif

