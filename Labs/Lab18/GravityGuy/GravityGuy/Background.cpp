/**********************************************************************************
// Background (Código Fonte)
// 
// Criação:		21 Abr 2012
// Atualização:	04 Jul 2019
// Compilador:	Visual C++ 2019

//
// Descrição:	Plano de fundo do jogo
//
**********************************************************************************/

#include "Background.h"

// ---------------------------------------------------------------------------------

Background::Background()
{
	// posição inicial do plano de fundo
	MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);
	xF = xB = x;

	// cria sprites do plano de fundo
	sky    = new Sprite("Resources/Sky.png");	
	backgF = new Sprite("Resources/BackgFront.png");
	backgB = new Sprite("Resources/BackgBack.png");	
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
	delete backgF;
	delete backgB;	
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
	sky->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

	backgB->Draw(xB, y, Layer::BACK);
	
	if (xB + backgB->Width()/2.0f < window->Width())
		backgB->Draw(xB + backgB->Width(), Y(), Layer::BACK);

	if (xB + backgB->Width()/2.0f < 0)
		xB += backgB->Width();

	backgF->Draw(xF, y, Layer::MIDBACK);
	
	if (xF + backgF->Width()/2.0f < window->Width())
		backgF->Draw(xF + backgF->Width(), window->Height()/2.0f, Layer::MIDBACK);

	if (xF + backgF->Width()/2.0f < 0)
		xF += backgF->Width();
}

// -------------------------------------------------------------------------------
