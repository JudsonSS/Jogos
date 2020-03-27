/**********************************************************************************
// Alien (Arquivo de Cabeçalho)
// 
// Criação:		21 Dez 2012
// Atualização: 28 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Alienígena do jogo Galaga
//
**********************************************************************************/

#ifndef _GALAGA_ALIEN_H_
#define _GALAGA_ALIEN_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"			// tipos específicos da engine
#include "Object.h"			// interface de object
#include "Sprite.h"			// interface de sprites
#include <string>			// string da biblioteca STL
using std::string;			// usa string sem std::

// ---------------------------------------------------------------------------------

class Alien : public Object
{
private:
	Sprite * sprite;
	float vel;

public:
	Alien(string filename);
	~Alien();

	void Update();
	void Draw();
};

// ---------------------------------------------------------------------------------

inline void Alien::Draw()
{ sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif