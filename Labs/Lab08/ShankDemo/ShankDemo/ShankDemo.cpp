/**********************************************************************************
// ShankDemo
//
// Criação:		20 Set 2011
// Atualização:	24 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	O programa testa a nova organização dos sprites 
//              através da classe base Object.
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Resources.h"
#include "Shank.h"

// ------------------------------------------------------------------------------

class ShankDemo : public Game
{
private:
	Sprite * backg   = nullptr;		// sprite para fundo da cena
	Image  * logoImg = nullptr;		// imagem do logotipo
	Sprite * logo1   = nullptr;		// sprite 1 do logotipo
	Sprite * logo2   = nullptr;		// sprite 2 do logotipo

	Shank  * shank   = nullptr;		// objeto do personagem shank

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};

// ------------------------------------------------------------------------------

void ShankDemo::Init()
{
	// inicializa objetos do jogo
	logoImg = new Image("Resources/Logo.png");
	logo1   = new Sprite(logoImg);
	logo2   = new Sprite(logoImg);
	backg   = new Sprite("Resources/Background.jpg");

	shank = new Shank();
}

// ------------------------------------------------------------------------------

void ShankDemo::Update()
{
	window->CloseOnEscape();

	shank->Update();
} 

// ------------------------------------------------------------------------------

void ShankDemo::Draw()
{
	// desenha objetos
	backg->Draw(0.0f, 0.0f, Layer::BACK);
	logo1->Draw(40.0f, 60.0f, Layer::MIDFRONT);
	logo2->Draw(400.0f, 450.0f, Layer::MIDBACK);

	shank->Draw();
}

// ------------------------------------------------------------------------------

void ShankDemo::Finalize()
{
	// remove objetos da memória
	delete backg;
	delete logoImg;
	delete logo1;
	delete logo2;

	delete shank;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Engine * engine = new Engine();

	// configura janela
	engine->window->Mode(WINDOWED);
	engine->window->Size(800, 600);
	engine->window->Color(0, 0, 0);
	engine->window->Title("Shank Demo");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	// configura dispositivo gráfico
	//engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new ShankDemo());

	// destrói o motor e o jogo
	delete engine;
	return status;
}

// ----------------------------------------------------------------------------

