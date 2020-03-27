/**********************************************************************************
// Home (Código Fonte) 
// 
// Criação:		18 Jan 2013
// Atualização: 04 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Tela de abertura do jogo PacMan
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
	backg = new Sprite("Resources/TitleScreen.jpg");
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
	delete backg;
}

// ------------------------------------------------------------------------------

void Home::Update()
{
	// sai do jogo com a tecla ESC
	if (window->KeyUp(VK_ESCAPE))
		ctrlKeyESC = true;
	if (ctrlKeyESC && window->KeyDown(VK_ESCAPE))
		window->Close();

	// passa ao primeiro nível com ENTER
	if (window->KeyDown(VK_RETURN))
		Engine::Next<Level1>();
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
	backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
}

// ------------------------------------------------------------------------------