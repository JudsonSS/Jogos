/**********************************************************************************
// Platform (Código Fonte)
// 
// Criação:		21 Abr 2012
// Atualização:	04 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType)
{
	switch (platType)
	{
	case SMALL:  platform = new Sprite("Resources/SmallGray.png"); break;
	case MEDIUM: platform = new Sprite("Resources/MediumGray.png"); break;
	case LARGE:  platform = new Sprite("Resources/LongGray.png"); break;
	}
	
	bbox = new Rect(-platform->Width()/2.0f, -platform->Height()/2.0f, platform->Width()/2.0f, platform->Height()/2.0f);
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
	// move plataforma apenas no eixo x
	Translate(-200.0f * gameTime, 0);
}

// -------------------------------------------------------------------------------
