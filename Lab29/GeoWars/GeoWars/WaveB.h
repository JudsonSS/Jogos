/**********************************************************************************
// WaveB (Arquivo de Cabeçalho)
//
// Criação:		06 Ago 2019
// Atualização:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Cria uma onda de inimigos Blue
//
**********************************************************************************/

#ifndef _GEOWARS_WAVEB_H_
#define _GEOWARS_WAVEB_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class WaveB : public Object
{
private:
	float pX, pY;				// posição dos inimigos 
	FloatRand posX;				// valor aleatório para posição X
	FloatRand posY;				// valor aleatório para posição Y
	FloatRand secs;				// valor aleatório de segundos
	Timer timer;				// medidor de tempo
	float delay;				// atraso para a próxima onda

public:
	WaveB();					// construtor
	~WaveB();					// destrutor

	void Update();				// atualização
	void Draw();				// desenho
};

// ------------------------------------------------------------------------------

#endif
