/**********************************************************************************
// Random (Arquivo de Cabeçalho)
//
// Criação:     03 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Gerador de números pseudoaleatórios
//
**********************************************************************************/

#ifndef _PROGJOGOS_RANDOM_H_
#define _PROGJOGOS_RANDOM_H_

// -------------------------------------------------------------------------------

#include "Types.h"                          // tipos específicos da engine
#include <random>                           // biblioteca random da STL
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

// -------------------------------------------------------------------------------

class Random
{
protected:
    static random_device seed;              // gerador não-determinístico
    static mt19937 mt;                      // gerador Mersenne Twister
};

// -------------------------------------------------------------------------------

class RandI : public Random
{
private:
    uniform_int_distribution<int> dist;     // distribuição uniforme

public:
    RandI(int min, int max);                // construtor    
    int Rand();                             // retorna número aleatório
};

// -------------------------------------------------------------------------------

class RandF : public Random
{
private:
    uniform_real_distribution<float> dist;  // distribuição uniforme

public:
    RandF(float min, float max);            // construtor    
    float Rand();                           // retorna número aleatório
};

// ---------------------------------------------------------------------------------

#endif
