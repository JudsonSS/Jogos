/**********************************************************************************
// Ship (Arquivo de Cabe�alho)
// 
// Cria��o:		14 Mar 2013
// Atualiza��o:	19 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Define uma nave espacial
//
**********************************************************************************/

#ifndef _INERTIA_SHIP_H_
#define _INERTIA_SHIP_H_

// ---------------------------------------------------------------------------------

#include "Vector.h"						// representa��o de vetor
#include "Object.h"						// objetos do jogo
#include "TileSet.h"					// folha de sprites
#include "Animation.h"					// desenho de anima��es
#include "Types.h"						// tipos espec�ficos da engine

// ---------------------------------------------------------------------------------

enum ShipAnims { INERTIA, FORWARD, BACKWARD };

// ---------------------------------------------------------------------------------

class Ship : public Object
{
private:
	TileSet * shipSet;					// folha de sprites 
	Animation * shipAni;				// anima��o da nave espacial
	
public:
	Vector direction;					// dire��o da nave
	Vector speed;						// velocidade da nave

	Ship();								// construtor	
	~Ship();							// destrutor

	void Forward();						// propuls�o para frente
	void Backward();					// propuls�o para tr�s

	void Rotate(float angle);			// sobrescreve m�todo de Object
	void Update();						// atualiza��o
	void Draw();						// desenho
}; 

// ---------------------------------------------------------------------------------

#endif