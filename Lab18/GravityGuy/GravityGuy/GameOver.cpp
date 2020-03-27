/**********************************************************************************
// GameOver (Arquivo de Cabeçalho)
// 
// Criação:		14 Fev 2013
// Atualização:	04 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Fim do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "GameOver.h"
#include "GravityGuy.h"
#include "Home.h"

// ----------------------------------------------------------------------

void GameOver::Init()
{
	title = new Sprite("Resources/GameOver.png");
}

// ----------------------------------------------------------------------

void GameOver::Update()
{
	if (window->KeyCtrl(VK_ESCAPE) || window->KeyCtrl(VK_RETURN))
		GravityGuy::NextLevel<Home>();
}

// ----------------------------------------------------------------------

void GameOver::Draw()
{
	title->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

// ----------------------------------------------------------------------

void GameOver::Finalize()
{
	delete title;
}

// ----------------------------------------------------------------------

