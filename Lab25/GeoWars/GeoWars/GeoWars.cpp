/**********************************************************************************
// GeoWars (Código Fonte)
// 
// Criação:		23 Out 2012
// Atualização:	05 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Demonstração de scrolling e IA
//
**********************************************************************************/

#include "Resources.h"
#include "GeoWars.h"
#include "Engine.h"	
#include "Magenta.h"
#include "Blue.h"	
#include "Green.h"
#include "Orange.h"
#include "Delay.h"

// ------------------------------------------------------------------------------

Player * GeoWars::player = nullptr;
Audio  * GeoWars::audio = nullptr;
Scene  * GeoWars::scene = nullptr;
bool     GeoWars::viewHUD = false;

// ------------------------------------------------------------------------------

void GeoWars::Init() 
{
	// cria sistema de áudio
	audio = new Audio();
	audio->Add(THEME, "Resources/Theme.wav");
	audio->Add(FIRE, "Resources/Fire.wav");
	audio->Add(HITWALL, "Resources/Hitwall.wav");
	audio->Add(EXPLODE, "Resources/Explode.wav");
	audio->Add(START, "Resources/Start.wav");

	// ajusta volumes
	audio->Volume(FIRE, 0.2f);
	audio->Volume(START, 0.8f);

	// carrega/incializa objetos
	backg   = new Background("Resources/Space.jpg");
	player  = new Player();
	scene   = new Scene();	

	// calcula posição para manter viewport centralizada
	float difx = (game->Width() - window->Width())/2.0f;
	float dify = (game->Height() - window->Height())/2.0f;

	// inicializa viewport para o centro do background
	viewport.left   = 0.0f + difx;
	viewport.right  = viewport.left + window->Width();
	viewport.top    = 0.0f + dify;
	viewport.bottom = viewport.top + window->Height();

	// cria o Heads Up Display
	hud = new Hud();

	// adiciona objetos na cena
	scene->Add(player, MOVING);
	scene->Add(new Magenta(player), STATIC);
	scene->Add(new Blue(player), STATIC);
	scene->Add(new Green(player), STATIC);
	scene->Add(new Orange(player), STATIC);
	scene->Add(new Delay(), STATIC);
}

// ------------------------------------------------------------------------------

void GeoWars::Update()
{
	// sai com o pressionamento da tecla ESC
	window->CloseOnEscape();

	// atualiza cena e calcula colisões
	scene->Update();
	scene->CollisionDetection();

	// ---------------------------------------------------
	// atualiza a viewport
	// ---------------------------------------------------
	viewport.left   = player->X() - window->CenterX();
	viewport.right  = player->X() + window->CenterX();
	viewport.top    = player->Y() - window->CenterY();
	viewport.bottom = player->Y() + window->CenterY();
			
	if (viewport.left < 0)
	{
		viewport.left  = 0;
		viewport.right = float(window->Width());
	}
	else if (viewport.right > game->Width())
	{  
		viewport.left  = float (game->Width() - window->Width());
 		viewport.right = float(game->Width());
	}
  		        
  	if (viewport.top < 0)
	{
		viewport.top  = 0;
		viewport.bottom = float(window->Height());
	}
	else if (viewport.bottom > game->Height())
	{
		viewport.top = float(game->Height() - window->Height());
		viewport.bottom = float(game->Height());
	}
	// ---------------------------------------------------

	// ativa ou desativa a bounding box
	if (window->KeyCtrl('B'))
		viewBBox = !viewBBox;

	// ativa ou desativa o heads up display
	if (window->KeyCtrl('H'))
		viewHUD = !viewHUD;
} 

// ------------------------------------------------------------------------------

void GeoWars::Draw()
{
	// desenha pano de fundo
	backg->Draw(viewport);

	// desenha heads up display
	if (viewHUD)
		hud->Draw();

	// desenha a cena
	scene->Draw();

	// desenha bounding box
	if (viewBBox)
		scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void GeoWars::Finalize()
{
	delete audio;
	delete hud;
	delete scene;
	delete backg;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// cria motor do jogo
	Engine * engine = new Engine();

	// configura janela
	//engine->window->Mode(WINDOWED);
	//engine->window->Size(1152, 648);
	engine->window->Color(0, 0, 0);
	engine->window->Title("GeoWars");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);
	engine->window->HideCursor(true);

	// configura dispositivo gráfico
	engine->graphics->VSync(false);

	// cria o jogo
	Game * game = new GeoWars();

	// configura o jogo
	game->Size(3840, 2160);
	
	// inicia execução
	int status = engine->Start(game);

	// destrói motor 
	delete engine;

	// encerra programa
	return status;
}

// ----------------------------------------------------------------------------