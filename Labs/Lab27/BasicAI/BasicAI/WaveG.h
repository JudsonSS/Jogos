/**********************************************************************************
// WaveG (Arquivo de Cabeçalho)
//
// Criação:     06 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos Green
//
**********************************************************************************/

#ifndef _BASICAI_WAVEG_H_
#define _BASICAI_WAVEG_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class WaveG : public Object
{
private: 
    RandF secs;             // valor aleatório de segundos
    Timer timer;            // medidor de tempo
    float delay;            // atraso para a próxima onda

public:
    WaveG();                // construtor
    ~WaveG();               // destrutor

    void Update();          // atualização
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
