/**********************************************************************************
// Ship (Arquivo de Cabeçalho)
// 
// Criação:     14 Mar 2013
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma nave espacial
//
**********************************************************************************/

#ifndef _INERTIA_SHIP_H_
#define _INERTIA_SHIP_H_

// ---------------------------------------------------------------------------------

#include "Vector.h"                     // representação de vetor
#include "Object.h"                     // objetos do jogo
#include "TileSet.h"                    // folha de sprites
#include "Animation.h"                  // desenho de animações
#include "Types.h"                      // tipos específicos da engine

// ---------------------------------------------------------------------------------

enum ShipAnims { INERTIA, FORWARD, BACKWARD };

// ---------------------------------------------------------------------------------

class Ship : public Object
{
private:
    TileSet * shipSet;                  // folha de sprites 
    Animation * shipAni;                // animação da nave espacial
    
public:
    Vector direction;                   // direção da nave
    Vector speed;                       // velocidade da nave

    Ship();                             // construtor    
    ~Ship();                            // destrutor

    void Forward();                     // propulsão para frente
    void Backward();                    // propulsão para trás

    void Rotate(float angle);           // sobrescreve método de Object
    void Update();                      // atualização
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------

#endif