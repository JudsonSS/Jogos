/**********************************************************************************
// Background (Arquivo de Cabeçalho)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#ifndef _PLATFORMER_BACKGROUND_H_
#define _PLATFORMER_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites

// ---------------------------------------------------------------------------------

class Background : public Object
{
private:
    float xF, xB;                       // posição horizontal dos sprites
    Image * imgF;                       // imagem de fundo frontal
    Image * imgB;                       // imagem de fundo traseira    

    Sprite * sky;                       // fundo estático
    Sprite * backgF1;                   // pano de fundo dinâmico (frontal 1)
    Sprite * backgF2;                   // pano de fundo dinâmico (frontal 2)
    Sprite * backgB1;                   // pano de fundo dinâmico (traseiro 1)
    Sprite * backgB2;                   // pano de fundo dinâmico (traseiro 2)

public:
    Background();                       // construtor
    ~Background();                      // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------

#endif