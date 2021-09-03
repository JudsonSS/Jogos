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

#include "Block.h"
#include "Breakout.h"

// ---------------------------------------------------------------------------------

Block::Block(Image * img)
{
    // tamanho do bloco é 60x24
    BBox(new Rect(0, 0, 59, 23));

    // sprite do bloco
    sprite  = new Sprite(img);

    // velocidades iniciais
    velX = 0.0f;
    velY = 0.0f;

    // tipo do objeto
    type = BLOCK;
}

// ---------------------------------------------------------------------------------

Block::~Block()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Block::Update()
{
    // desloca o bloco
    Translate(velX * gameTime, velY * gameTime);

    // destrói ao sair da janela
    if (y > window->Height())
        Breakout::scene->Delete();
}

// ---------------------------------------------------------------------------------
