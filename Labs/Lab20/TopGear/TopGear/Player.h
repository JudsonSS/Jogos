/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:     12 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   O carro do jogador
//
**********************************************************************************/

#ifndef _TOPGEAR_PLAYER_H_
#define _TOPGEAR_PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // animação de sprites
#include "Types.h"               // tipos específicos do motor
#include "Font.h"                // desenho de texto 
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

enum Direction { STRAIGHT, LEFT, RIGHT };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet * carSet;           // folha de sprites do carro
    Animation * carAni;         // animação do carro
    Font * speedFont;           // fonte para exibir a velocidade
    float & speed;              // velocidade do carro
    stringstream text;          // exibição de texto

public:
    Player();                   // construtor
    ~Player();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
}; 

// ---------------------------------------------------------------------------------

#endif