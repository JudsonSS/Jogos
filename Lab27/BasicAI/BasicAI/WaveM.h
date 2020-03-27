/**********************************************************************************
// WaveM (Arquivo de Cabeçalho)
//
// Criação:		06 Ago 2019
// Atualização:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Cria uma onda de inimigos Magenta
//
**********************************************************************************/

#ifndef _BASICAI_WAVEM_H_
#define _BASICAI_WAVEM_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class WaveM : public Object
{
private:
	float pX, pY;				// posição dos inimigos 
	FloatRand posX;				// valor aleatório para posição X
	FloatRand posY;				// valor aleatório para posição Y
	FloatRand secs;				// valor aleatório de segundos
	Timer timer;				// medidor de tempo
	float delay;				// atraso para a próxima onda

public:
	WaveM();						// construtor
	~WaveM();					// destrutor

	void Update();				// atualização
	void Draw();				// desenho
};

// ------------------------------------------------------------------------------

#endif
