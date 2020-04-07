/**********************************************************************************
// Platform (Código Fonte)
// 
// Criação:		21 Abr 2012
// Atualização:	11 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType)
{
	// configura objeto
	MoveTo(posX, posY, 0.4f);

	switch (platType)
	{
	case SMALL:  platform = new Sprite("Resources/SmallGray.png"); break;
	case MEDIUM: platform = new Sprite("Resources/MediumGray.png"); break;
	case LARGE:  platform = new Sprite("Resources/LongGray.png"); break;
	}
	
	bbox = new Rect(
		x - platform->Width()/2.0f, 
		y - platform->Height()/2.0f, 
		x + platform->Width()/2.0f,		
		y + platform->Height()/2.0f);
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
	delete platform;
	delete bbox;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
	// move plataforma
	Translate(-200.0f * gameTime, 0);
}

// -------------------------------------------------------------------------------
