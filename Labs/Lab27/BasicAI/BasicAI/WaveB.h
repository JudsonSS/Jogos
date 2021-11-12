/**********************************************************************************
// WaveB (Arquivo de Cabeçalho)
//
// Criação:     06 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos Blue
//
**********************************************************************************/

#ifndef _BASICAI_WAVEB_H_
#define _BASICAI_WAVEB_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class WaveB : public Object
{
private:
    float pX, pY;           // posição dos inimigos 
    RandF posX;             // valor aleatório para posição X
    RandF posY;             // valor aleatório para posição Y
    RandF secs;             // valor aleatório de segundos
    Timer timer;            // medidor de tempo
    float delay;            // atraso para a próxima onda

public:
    WaveB();                // construtor
    ~WaveB();               // destrutor

    void Update();          // atualização
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
