/**********************************************************************************
// Missile (Arquivo de Cabe�alho)
// 
// Cria��o:		21 Dez 2012
// Atualiza��o:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Representa um m�ssil
//
**********************************************************************************/

#ifndef _PATTERNS_MISSILE_H_
#define _PATTERNS_MISSILE_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"					// tipos espec�ficos da engine
#include "Object.h"					// interface de object
#include "Sprite.h"					// interface de sprites
#include "Image.h"					// interface de image

// ---------------------------------------------------------------------------------

class Missile : public Object
{
private:
	Sprite * sprite;				// sprite do m�ssil
	float vel;						// velocidade

public:
	Missile(Image * img);			// construtor
	~Missile();						// destrutor

	void Update();					// atualiza��o do objeto
	void Draw();					// desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��es Membro Inline

inline void Missile::Draw()
{  sprite->Draw(x, y, Layer::MIDFRONT); }

// ---------------------------------------------------------------------------------

#endif