/**********************************************************************************
// Cars (Arquivo de Cabeçalho)
//
// Criação:     14 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Carros adversários
//
**********************************************************************************/

#ifndef _TOPGEAR_CARS_H_
#define _TOPGEAR_CARS_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                 // objetos do jogo 
#include "Sprite.h"                 // desenho de sprites
#include "Types.h"                  // tipos específicos do motor

// ---------------------------------------------------------------------------------

class Cars : public Object
{
private:
    Sprite * sprite;                // sprite do carro branco
    float deltaX;                   // valor do deslocamento eixo X
    float deltaY;                   // valor do deslocamento eixo Y
    float speed;                    // velocidade do carro

public:
    Cars();                         // construtor
    ~Cars();                        // destrutor

    void Update();                  // atualização
    void Draw();                    // desenho
};

// ---------------------------------------------------------------------------------

#endif

