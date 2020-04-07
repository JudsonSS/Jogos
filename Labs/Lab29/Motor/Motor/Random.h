/**********************************************************************************
// Random (Arquivo de Cabeçalho)
//
// Criação:		03 Ago 2019
// Atualização:	12 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Gerador de números pseudoaleatórios
//
**********************************************************************************/

#ifndef _DESENVJOGOS_RANDOM_H_
#define _DESENVJOGOS_RANDOM_H_

#ifdef MOTOR_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// -------------------------------------------------------------------------------

#include "Types.h"							// tipos específicos da engine
#include <random>							// biblioteca random da STL
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

// -------------------------------------------------------------------------------

class DLL Random
{
protected:
	static random_device seed;				// gerador não-determinístico
	static mt19937 mt;						// gerador Mersenne Twister
};

// -------------------------------------------------------------------------------

class DLL IntRand : public Random
{
private:
	uniform_int_distribution<int> dist;		// distribuição uniforme

public:
	IntRand(int min, int max);				// construtor	
	int Rand();								// retorna número aleatório
};

// -------------------------------------------------------------------------------

class DLL FloatRand : public Random
{
private:
	uniform_real_distribution<float> dist;	// distribuição uniforme

public:
	FloatRand(float min, float max);		// construtor	
	float Rand();							// retorna número aleatório
};

// ---------------------------------------------------------------------------------

#endif
