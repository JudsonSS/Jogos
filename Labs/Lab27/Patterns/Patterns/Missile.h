/**********************************************************************************
// Missile (Arquivo de Cabeçalho)
// 
// Criação:		21 Dez 2012
// Atualização:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Representa um míssil
//
**********************************************************************************/

#ifndef _PATTERNS_MISSILE_H_
#define _PATTERNS_MISSILE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"					// tipos específicos da engine
#include "Object.h"					// interface de object
#include "Sprite.h"					// interface de sprites
#include "Image.h"					// interface de image

// ---------------------------------------------------------------------------------

class Missile : public Object
{
private:
	Sprite * sprite;				// sprite do míssil
	float vel;						// velocidade

public:
	Missile(Image * img);			// construtor
	~Missile();						// destrutor

	void Update();					// atualização do objeto
	void Draw();					// desenho do objeto
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline

inline void Missile::Draw()
{  sprite->Draw(x, y, Layer::MIDFRONT); }

// ---------------------------------------------------------------------------------

#endif