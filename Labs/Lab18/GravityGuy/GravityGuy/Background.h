/**********************************************************************************
// Background (Arquivo de Cabeçalho)
// 
// Criação:		21 Abr 2012
// Atualização:	04 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Plano de fundo do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_BACKGROUND_H_
#define _GRAVITYGUY_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"						// tipos específicos da engine
#include "Object.h"						// interface de Object
#include "Sprite.h"						// desenho de sprites

// ---------------------------------------------------------------------------------

class Background : public Object
{
private:
	Sprite * backgF;					// background front
	Sprite * backgB;					// background back
	Sprite * sky;						// fundo estático do background
	float xF, xB;						// posição horizontal dos sprites

public:
	Background();						// construtor
	~Background();						// destrutor

	void Update();						// atualização do objeto
	void Draw();						// desenho do objeto
}; 

// ---------------------------------------------------------------------------------

#endif