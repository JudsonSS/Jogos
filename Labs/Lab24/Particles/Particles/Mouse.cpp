/**********************************************************************************
// Mouse (Código Fonte)
// 
// Criação:		14 Mai 2012
// Atualização:	29 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Gerencia um objeto mouse na tela
//
**********************************************************************************/

#include "Mouse.h"

// ---------------------------------------------------------------------------------

Mouse::Mouse()
{
	sprite = new Sprite("Resources/Mouse.png");
	MoveTo(window->CenterX(), window->CenterY(), Layer::MIDFRONT);
}

// ---------------------------------------------------------------------------------

Mouse::~Mouse()
{
	delete sprite;
}

// -------------------------------------------------------------------------------

void Mouse::Update()
{
	MoveTo(window->MouseX(), window->MouseY());
	
	if (x > window->Width())   
		MoveTo(float(window->Width()), y);
	if (y > window->Height())  
		MoveTo(x, float(window->Height()));
	if (x < 0) 
		MoveTo(0, y);
	if (y < 0) 
		MoveTo(x, 0);
}

// -------------------------------------------------------------------------------