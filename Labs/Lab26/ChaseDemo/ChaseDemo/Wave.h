/**********************************************************************************
// Wave (Arquivo de Cabeçalho)
//
// Criação:     06 Ago 2019
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos
//
**********************************************************************************/

#ifndef _CHASEDEMO_WAVE_H_
#define _CHASEDEMO_WAVE_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class Wave : public Object
{
private:
    float pX, pY;               // posição dos inimigos 
    RandF posX;                 // valor aleatório para posição X
    RandF posY;                 // valor aleatório para posição Y
    RandF secs;                 // valor aleatório de segundos
    Timer timer;                // medidor de tempo
    float delay;                // atraso para a próxima onda

public:
    Wave();                     // construtor
    ~Wave();                    // destrutor

    void Update();              // atualização
    void Draw();                // desenho
};

// ------------------------------------------------------------------------------

#endif
