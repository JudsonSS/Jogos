/**********************************************************************************
// Missile (Arquivo de Cabeçalho)
// 
// Criação:     23 Nov 2011
// Atualização: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para um míssil/projétil
//
**********************************************************************************/

#ifndef _VECTOR2D_MISSILE_H_
#define _VECTOR2D_MISSILE_H_

// --------------------------------------------------------------------------------

#include "Object.h"                             // objetos do jogo 
#include "Image.h"                              // carregamento de imagens
#include "Sprite.h"                             // desenho de sprites
#include "Vector.h"                             // representação de vetor
#include "Plane.h"                              // objeto avião

// --------------------------------------------------------------------------------

class Missile : public Object
{
public:
    Sprite * sprite;                            // sprite do míssil
    Vector speed;                               // velocidade do míssil

public:
    Missile(Plane * plane, Image * img);        // construtor
    ~Missile();                                 // destrutor

    void Update();                              // atualização
    void Draw();                                // desenho
}; 

// ------------------------------------------------------------------------------

#endif