/**********************************************************************************
// Block (Arquivo de Cabeçalho)
// 
// Criação:     22 Dez 2012
// Atualização: 20 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Bloco do jogo Breakout
//
**********************************************************************************/

#ifndef _BREAKOUT_BLOCK_H_
#define _BREAKOUT_BLOCK_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"              // tipos específicos da engine
#include "Object.h"             // interface de Object
#include "Sprite.h"             // interface de Sprites

// ---------------------------------------------------------------------------------

class Block : public Object
{
private:
    Sprite * sprite;            // sprite do bloco

public:
    float velX;                 // velocidade horizontal
    float velY;                 // velocidade vertical

    Block(Image * img);         // construtor
    ~Block();                   // destrutor

    void Update();              // atualização do objeto
    void Draw();                // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Block::Draw()
{ sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif