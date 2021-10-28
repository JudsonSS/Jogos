/**********************************************************************************
// Missile (Arquivo de Cabeçalho)
// 
// Criação:     23 Nov 2011
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para um míssil/projétil
//
**********************************************************************************/

#ifndef _ASTEROIDS_MISSILE_H_
#define _ASTEROIDS_MISSILE_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Ship.h" 

// --------------------------------------------------------------------------------

class Missile : public Object
{
private:
    Sprite * sprite;            // sprite do míssil
    Vector   speed;             // velocidade do míssil
    
public:
    Missile(Ship * ship);       // construtor
    ~Missile();                 // destrutor

    void Update();              // atualização
    void Draw();                // desenho
}; 

// ------------------------------------------------------------------------------

#endif