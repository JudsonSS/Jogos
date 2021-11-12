/**********************************************************************************
// WaveO (Arquivo de Cabeçalho)
//
// Criação:     06 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos Orange
//
**********************************************************************************/

#ifndef _BASICAI_WAVEO_H_
#define _BASICAI_WAVEO_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class WaveO : public Object
{
private:
    int numX, numY;         // número de inimigos que cabem na tela
    float posX, posY;       // posição dos inimigos 
    RandI position;         // valor aleatório para posição
    RandF delay;            // valor aleatório para tempo
    Timer timer;            // medidor de tempo
    float waveDelay;        // atraso para a próxima onda
    bool newWave;           // enviar nova onda

public:
    WaveO();                // construtor
    ~WaveO();               // destrutor

    void Update();          // atualização
    void Draw();            // desenho
};

// ------------------------------------------------------------------------------

#endif
