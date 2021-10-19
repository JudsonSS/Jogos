/**********************************************************************************
// Ball (Arquivo de Cabeçalho)
// 
// Criação:     23 Nov 2011
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para uma bala de canhão
//
**********************************************************************************/

#ifndef _PROJECTILE_BALL_H_
#define _PROJECTILE_BALL_H_

// --------------------------------------------------------------------------------

#include "Vector.h"                             // representação de vetor
#include "Object.h"                             // objetos do jogo
#include "Sprite.h"                             // desenho de sprites
#include "Cannon.h"                             // objeto canhão

// --------------------------------------------------------------------------------

class Ball : public Object
{
private:
    Sprite * sprite;                            // sprite da bala
    Vector   speed;                             // velocidade da bala
    
public:
    static bool airResistance;                  // resistência do ar

    Ball(Cannon * cannon);                      // construtor
    ~Ball();                                    // destrutor

    void Update();                              // atualização 
    void Draw();                                // desenho
}; 

// ------------------------------------------------------------------------------

#endif