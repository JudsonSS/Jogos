/**********************************************************************************
// AnimaMax (Código Fonte)
// 
// Criação:		10 Abr 2012
// Atualização: 06 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Exemplo de uso da classe Animation
//
**********************************************************************************/

#include "Engine.h"
#include "AnimaMax.h"
#include "Explosion.h"
#include "Resources.h"

// -----------------------------------------------------------------------------

Scene * AnimaMax::scene = nullptr;

// -----------------------------------------------------------------------------

void AnimaMax::Init()
{
	scene   = new Scene();
	bar     = new Sprite("Resources/Bar.png");
	backg   = new Sprite("Resources/Background.jpg");
	tileset = new TileSet("Resources/Explosion.png", 192, 192, 5, 25);
	keyCtrl = false;
}

// ------------------------------------------------------------------------------

void AnimaMax::Update()
{
	window->CloseOnEscape();

	// gera explosões com a barra de espaços
	if (window->KeyDown(VK_SPACE))
	{
		Explosion * explo = new Explosion(tileset);
		explo->MoveTo(float(rand() % window->Width()), float(rand() % window->Height()));
		scene->Add(explo, STATIC);
	}

	// gera explosões com a tecla ENTER
	if (!keyCtrl && window->KeyUp(VK_RETURN))
		keyCtrl = true;

	if (keyCtrl && window->KeyDown(VK_RETURN))
	{
		Explosion * explo = new Explosion(tileset);
		explo->MoveTo(float(rand() % window->Width()), float(rand() % window->Height()));
		scene->Add(explo, STATIC);
		keyCtrl = false;
	}

	scene->Update();
} 

// ------------------------------------------------------------------------------

void AnimaMax::Draw()
{
	backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	bar->Draw(float(window->CenterX()), window->CenterY() + 45.0f);
	scene->Draw();
} 

// ------------------------------------------------------------------------------

void AnimaMax::Finalize()
{
	delete bar;
	delete backg;
	delete tileset;
	delete scene;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Engine * engine = new Engine();

	// configura janela
	engine->window->Mode(WINDOWED);
	engine->window->Size(960, 540);
	engine->window->Color(0, 0, 0);
	engine->window->Title("AnimaMax");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	// configura dispositivo gráfico
	//engine->graphics->VSync(true);
	
	// inicia o jogo
	int status = engine->Start(new AnimaMax());

	delete engine;
	return status;
}

// ----------------------------------------------------------------------------

