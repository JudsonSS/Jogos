/**********************************************************************************
// BasicAI (Código Fonte)
// 
// Criação:		23 Out 2012
// Atualização:	11 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Demonstração de scrolling e IA
//
**********************************************************************************/

#include "Resources.h"
#include "BasicAI.h"
#include "Engine.h"	
#include "Delay.h"

// ------------------------------------------------------------------------------

Player * BasicAI::player = nullptr;
Audio  * BasicAI::audio = nullptr;
Scene  * BasicAI::scene = nullptr;
bool     BasicAI::viewHUD = false;

// ------------------------------------------------------------------------------

void BasicAI::Init() 
{
	// cria sistema de áudio
	audio = new Audio();
	audio->Add(START, "Resources/Start.wav");
	audio->Add(THEME, "Resources/Theme.wav");
	audio->Add(FIRE, "Resources/Fire.wav", 2);
	audio->Add(HITWALL, "Resources/Hitwall.wav", 5);
	audio->Add(EXPLODE, "Resources/Explode.wav", 5);
	audio->Add(ORANGE, "Resources/Orange.wav", 1);
	audio->Add(MAGENTA, "Resources/Magenta.wav", 2);
	audio->Add(BLUE, "Resources/Blue.wav", 2);
	audio->Add(GREEN, "Resources/Green.wav", 2);

	// ajusta volumes
	audio->Volume(START, 0.80f);
	audio->Volume(FIRE, 0.20f);
	audio->Volume(EXPLODE, 0.25f);
	audio->Volume(ORANGE, 0.90f);	
	audio->Volume(MAGENTA, 0.50f);
	audio->Volume(BLUE, 0.20f);
	audio->Volume(GREEN, 0.75f);

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
	scene->Add(new Delay(), STATIC);
}

// ------------------------------------------------------------------------------

void BasicAI::Update()
{
	// sai com o pressionamento da tecla ESC
	window->CloseOnEscape();

	// atualiza cena e calcula colisões
	scene->Update();
	scene->CollisionDetection();

	// atualiza o heads up display
	hud->Update();

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

void BasicAI::Draw()
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

void BasicAI::Finalize()
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
	engine->window->Title("BasicAI");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);
	engine->window->HideCursor(true);

	// configura dispositivo gráfico
	engine->graphics->VSync(false);

	// cria o jogo
	Game * game = new BasicAI();

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