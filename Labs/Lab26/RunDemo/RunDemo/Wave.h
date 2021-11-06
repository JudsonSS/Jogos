/**********************************************************************************
// Wave (Arquivo de Cabeçalho)
//
// Criação:     06 Ago 2019
// Atualização: 05 Ago 2019
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos
//
**********************************************************************************/

#ifndef _RUNDEMO_WAVE_H_
#define _RUNDEMO_WAVE_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class Wave : public Object
{
private: 
    RandF secs;             // valor aleatório de segundos
    Timer timer;            // medidor de tempo
    float delay;            // atraso para a próxima onda

public:
    Wave();                 // construtor
    ~Wave();                // destrutor

    void Update();          // atualização
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
