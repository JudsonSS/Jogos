/**********************************************************************************
// Sound Distance
// 
// Criação:		14 Out 2011
// Atualização:	28 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Ajusta volume pela distância do som
//
**********************************************************************************/

#include "SoundDist.h"
#include "Engine.h"

// ------------------------------------------------------------------------------

Scene * SoundDist::scene = nullptr;
Audio * SoundDist::audio = nullptr;

// ------------------------------------------------------------------------------

void SoundDist::Init() 
{	
	scene = new Scene();
	audio = new Audio();

	// adiciona e ajusta sons
	audio->Add(PULSE, "Resources/Pulse.wav", 3);
	audio->Add(EXPLOSION, "Resources/Explosion.wav", 3);
	audio->Volume(PULSE, 0.02f);

	// sprite de pano de fundo da cena
	backg = new Sprite("Resources/Space.jpg");

	// cria jogador
	Player * player = new Player();
	scene->Add(player, STATIC);

	// cria barras para limitar espaço
	Bar * bar = new Bar();
	bar->MoveTo(window->CenterX(), window->CenterY() - 220);
	scene->Add(bar, STATIC);

	bar = new Bar();
	bar->MoveTo(window->CenterX() - 175, window->CenterY() - 90);
	scene->Add(bar, STATIC);

	bar = new Bar();
	bar->MoveTo(window->CenterX() + 175, window->CenterY() - 90);
	scene->Add(bar, STATIC);

	bar = new Bar();
	bar->MoveTo(window->CenterX() - 300, window->CenterY() + 50);
	scene->Add(bar, STATIC);

	bar = new Bar();
	bar->MoveTo(window->CenterX() + 300, window->CenterY() + 50);
	scene->Add(bar, STATIC);
	
	// variáveis de controle
	keyCtrl = false;
	viewBBox = false;
}

// ------------------------------------------------------------------------------

void SoundDist::Update()
{
	window->CloseOnEscape();

	// habilita/desabilita bounding box
	if (window->KeyUp('B'))
		keyCtrl = true;	
	if (keyCtrl && window->KeyDown('B'))
	{
		viewBBox = !viewBBox;
		keyCtrl = false;
	}

	// atualiza cena e calcula colisões
	scene->Update();
	scene->CollisionDetection();
} 

// ------------------------------------------------------------------------------

void SoundDist::Draw()
{
	// desenha cena do jogo
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
	scene->Draw();	

	if (viewBBox)
	{
		// desenha bounding box dos objetos
		Engine::renderer->BeginPixels();
		scene->Begin();
		Object * obj = nullptr;
		while (obj = scene->Next())
			if (obj->bbox)
				Engine::renderer->Draw(obj->bbox, 0xffff00ff);
		Engine::renderer->EndPixels();
	}
} 

// ------------------------------------------------------------------------------

void SoundDist::Finalize()
{
	delete backg;
	delete audio;
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
	engine->window->Size(800, 600);
	engine->window->Color(0, 0, 0);
	engine->window->Title("Sound Distance");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	// configura dispositivo gráfico
	//engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new SoundDist());

	delete engine;
	return status;
}

// ----------------------------------------------------------------------------

