/**********************************************************************************
// Background (Arquivo de Cabeçalho)
// 
// Criação:		21 Abr 2012
// Atualização: 11 Jun 2019
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
#include "Sprite.h"						// background é composto por sprites

// ---------------------------------------------------------------------------------

class Background : public Object
{
private:
	float xF, xB;						// posição horizontal dos sprites
	Image * backgF;						// imagem front
	Image * backgB;						// imagem back	
	Sprite * backgF1;					// background front A
	Sprite * backgF2;					// background front B
	Sprite * backgB1;					// background back A
	Sprite * backgB2;					// background back B
	Sprite * sky;						// fundo estático do background

public:
	Background();						// construtor
	~Background();						// destrutor

	void Update();						// atualização do objeto
	void Draw();						// desenho do objeto
}; 

// ---------------------------------------------------------------------------------

#endif