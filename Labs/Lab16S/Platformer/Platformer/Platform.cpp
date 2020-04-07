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
	// define o tipo de plataforma
	switch (platType)
	{
	case SMALL:  type = SMALL; platform = new Sprite("Resources/SmallGray.png"); break;
	case MEDIUM: type = MEDIUM; platform = new Sprite("Resources/MediumGray.png"); break;
	case LARGE:  type = LARGE; platform = new Sprite("Resources/LongGray.png"); break;
	}

	// constrói bounding box
	bbox = new Rect(
		-platform->Width()/2.0f, 
		-platform->Height()/2.0f, 
		platform->Width()/2.0f,		
		platform->Height()/2.0f);
	
	// posiciona a plataforma
	MoveTo(posX, posY, Layer::MIDDLE);
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
