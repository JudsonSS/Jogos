/**********************************************************************************
// Background (Código Fonte)
// 
// Criação:		21 Abr 2012
// Atualização: 11 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Plano de fundo do jogo
//
**********************************************************************************/

#include "Background.h"

// ---------------------------------------------------------------------------------

Background::Background()
{
	MoveTo(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	xF = xB = x;

	// cria sprites do plano de fundo
	backgF = new Image("Resources/BackgFront.png");
	backgB = new Image("Resources/BackgBack.png");

	sky     = new Sprite("Resources/Sky.png");	
	backgF1 = new Sprite(backgF);
	backgF2 = new Sprite(backgF);
	backgB1 = new Sprite(backgB);
	backgB2 = new Sprite(backgB);
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
	delete backgF;
	delete backgB;	
	delete backgF1;
	delete backgF2;
	delete backgB1;
	delete backgB2;
	delete sky;
}

// -------------------------------------------------------------------------------

void Background::Update()
{
	// move sprites com velocidades diferentes
	xF -= 200 * gameTime;
	xB -= 150 * gameTime;
}

// -------------------------------------------------------------------------------

void Background::Draw()
{
	sky->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);

	backgB1->Draw(xB, y, Layer::MIDBACK);
	
	if (xB + backgB->Width()/2.0f < window->Width())
		backgB2->Draw(xB + backgB->Width(), y, Layer::MIDBACK);

	if (xB + backgB->Width()/2.0f < 0)
		xB += backgB->Width();

	backgF1->Draw(xF, y, Layer::MIDDLE);
	
	if (xF + backgF->Width()/2.0f < window->Width())
		backgF2->Draw(xF + backgF->Width(), window->Height()/2.0f, Layer::MIDDLE);

	if (xF + backgF->Width()/2.0f < 0)
		xF += backgF->Width();
}

// -------------------------------------------------------------------------------
