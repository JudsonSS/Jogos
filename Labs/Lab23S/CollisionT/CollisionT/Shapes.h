/**********************************************************************************
// Shapes (Arquivo de Cabeçalho)
//
// Criação:		27 Jul 2019
// Atualização:	27 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Objetos de diferentes formas
//
**********************************************************************************/

#ifndef _COLLISIONT_SHAPES_H_
#define _COLLISIONT_SHAPES_H_

// ---------------------------------------------------------------------------------

#include "Movable.h"

// ---------------------------------------------------------------------------------

class Box : public Movable
{
public:
	Box();									// construtor
	~Box();									// destrutor
};

// ---------------------------------------------------------------------------------

class Wheel : public Movable
{
public:
	Wheel();								// construtor
	~Wheel();								// destrutor
};

// ---------------------------------------------------------------------------------

class Drop : public Movable
{
public:
	Drop();									// construtor
	~Drop();								// destrutor
};

// ---------------------------------------------------------------------------------

class Plane : public Movable
{
public:
	Plane();								// construtor
	~Plane();								// destrutor
};

// ---------------------------------------------------------------------------------

class Hammer : public Movable
{
public:
	Hammer();								// construtor
	~Hammer();								// destrutor
};

// ---------------------------------------------------------------------------------

class Display : public Movable
{
public:
	Display();								// construtor
	~Display();								// destrutor
};

// ---------------------------------------------------------------------------------

class Ball : public Movable
{
public:
	Ball();									// construtor
	~Ball();								// destrutor
};

// ---------------------------------------------------------------------------------

class Dot : public Movable
{
public:
	Dot();									// construtor
	~Dot();									// destrutor
};

// ---------------------------------------------------------------------------------

class Bolt : public Movable
{
public:
	Bolt();									// construtor
	~Bolt();								// destrutor
};

// ---------------------------------------------------------------------------------

class House : public Movable
{
public:
	House();								// construtor
	~House();								// destrutor
};

// ---------------------------------------------------------------------------------

#endif
