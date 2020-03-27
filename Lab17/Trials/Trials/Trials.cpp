/**********************************************************************************
// Trials (Código Fonte)
// 
// Criação:		14 Mai 2012
// Atualização:	03 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Exemplo de interface com menus
//
**********************************************************************************/

#include "Engine.h"
#include "Trials.h"
#include "Mouse.h"
#include "Item.h"

// ------------------------------------------------------------------------------

void Trials::Init() 
{
	// cria gerenciadores
	scene = new Scene();
	audio = new Audio();

	// carrega sons e música
	audio->Add(EVOLUTION, "Resources/Evolution.wav");
	audio->Play(EVOLUTION, true);	

	// cria sprites
	backg = new Sprite("Resources/Trials.jpg");
	
	// cria objeto mouse
	mouse = new Mouse();

	// cria itens de menu
	menu[0] = new Item(570, 250, SINGLE,      "Resources/SinglePlayer.png");
	menu[1] = new Item(570, 305, MULTI,       "Resources/MultiPlayer.png");
	menu[2] = new Item(570, 360, TRACKS,      "Resources/TrackCentral.png");
	menu[3] = new Item(570, 435, LEADERBOARD, "Resources/Leaderboards.png");
	menu[4] = new Item(570, 490, OPTIONS,     "Resources/HelpOptions.png");
	menu[5] = new Item(570, 545, EXIT,        "Resources/ExitGame.png");
}

// ------------------------------------------------------------------------------

void Trials::Update()
{
	// fecha a janela ao pressionar ESC
	window->CloseOnEscape();

	// atualiza objeto mouse
	mouse->Update();

	// destaca item selecionado
	for (int i = 0; i < MaxItens; ++i)
	{
		if (scene->Collision(mouse, menu[i]))
		{
			menu[i]->Select();

			// executa ações do menu 
			if (mouse->Clicked())
			{
				switch (menu[i]->Type())
				{
				case SINGLE:
				case MULTI:
				case TRACKS:
				case LEADERBOARD:
				case OPTIONS: break;
				case EXIT: window->Close(); break;
				}
			}
		}
		else
		{
			menu[i]->UnSelect();
		}

		menu[i]->Update();
	}

	// habilita/desabilita bounding box
	if (window->KeyCtrl('B'))
		viewBBox = !viewBBox;
} 

// ------------------------------------------------------------------------------

void Trials::Draw()
{
	// desenha pano de fundo
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

	// desenha itens do menu
	for (int i = 0; i < MaxItens; ++i)
		menu[i]->Draw();

	// desenha bounding box dos menus
	if (viewBBox)
	{
		Engine::renderer->BeginPixels();
		
		Engine::renderer->Draw(mouse->bbox, 0xffff00ff);
		for (int i = 0; i < MaxItens; ++i)
			Engine::renderer->Draw(menu[i]->bbox, 0xffff00ff);

		Engine::renderer->EndPixels();
	}
} 

// ------------------------------------------------------------------------------

void Trials::Finalize()
{
	// remove gerenciadores
	delete scene;
	delete audio;

	// remove sprites
	delete backg;

	// remove objetos
	delete mouse;
	for (int i = 0; i < MaxItens; ++i)
		delete menu[i];
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
	engine->window->Title("Trials");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	// configura dispositivo gráfico
	//engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new Trials());

	delete engine;
	return status;
}

// ----------------------------------------------------------------------------

