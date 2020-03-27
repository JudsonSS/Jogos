/**********************************************************************************
// Click (Código Fonte)
//
// Criação:		29 Jun 2019
// Atualização:	03 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Click do Mouse
//
**********************************************************************************/

#include "Click.h"
#include "Balloons.h"

// ---------------------------------------------------------------------------------

Click::Click(TileSet * tiles)
{
	anim = new Animation(tiles, 0.030f, false);
	bbox = new Point();
}

// ---------------------------------------------------------------------------------

Click::~Click()
{
	delete bbox;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Click::Update()
{
	// segue a posição do mouse
	MoveTo(window->MouseX(), window->MouseY());
	
	// atualiza a animação
	anim->NextFrame();
	if (anim->Inactive())
		Balloons::scene->Delete();
}

// ---------------------------------------------------------------------------------