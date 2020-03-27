/**********************************************************************************
// Fireworks (Arquivo de Cabeçalho)
// 
// Criação:		17 Mar 2013
// Atualização:	31 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#ifndef _REFINERY_FIREWORKS_H_
#define _REFINERY_FIREWORKS_H_

// ---------------------------------------------------------------------------------

#include "Object.h"	
#include "Types.h"
#include "Particles.h"

// ---------------------------------------------------------------------------------

class Fireworks : public Object
{
private:
	Particles * starsGen;				// sistema de partículas
	
public:
	Fireworks();						// construtor
	~Fireworks();						// destrutor

	int  Size();						// quantidade de partículas
	void Update();						// atualização
	void Draw();						// desenho
}; 

// ---------------------------------------------------------------------------------

inline int Fireworks::Size()
{	return starsGen->Size(); }

inline void Fireworks::Draw()
{	starsGen->Draw(Layer::MIDDLE, 0.0f); }

// ---------------------------------------------------------------------------------


#endif