/**********************************************************************************
// TiledScroll (Código Fonte)
//
// Criação:		22 Out 2012
// Atualização:	14 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Desenhando e movimentando um background formado por blocos
//
**********************************************************************************/

#include "Engine.h"
#include "TiledScroll.h"

// ------------------------------------------------------------------------------

void TiledScroll::Init()
{
	int MapData[30 * 20] =
	{
		81, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 5, 79, 158, 38,
		91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 48, 79, 158, 38,
		91, 4, 114, 52, 4, 4, 4, 114, 4, 14, 96, 4, 4, 4, 52, 114, 4, 4, 4, 4, 4, 64, 4, 114, 4, 107, 58, 59, 158, 38,
		91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 52, 4, 4, 4, 4, 4, 107, 56, 58, 158, 158, 38,
		91, 4, 96, 4, 4, 102, 102, 102, 102, 102, 102, 113, 4, 4, 4, 4, 4, 4, 114, 4, 4, 4, 4, 107, 96, 77, 79, 158, 19, 38,
		91, 4, 4, 4, 93, 1, 2, 2, 2, 2, 3, 101, 4, 4, 4, 4, 137, 4, 4, 4, 4, 84, 107, 77, 77, 77, 68, 158, 158, 38,
		91, 4, 4, 93, 44, 11, 72, 71, 34, 72, 13, 111, 91, 4, 4, 4, 4, 114, 114, 4, 4, 4, 87, 77, 135, 77, 77, 68, 156, 38,
		91, 4, 4, 93, 111, 11, 33, 72, 72, 72, 13, 111, 91, 4, 4, 4, 4, 4, 4, 4, 14, 4, 4, 87, 77, 77, 77, 48, 158, 38,
		91, 4, 4, 93, 111, 11, 72, 72, 71, 12, 72, 3, 91, 4, 4, 4, 96, 4, 4, 4, 4, 24, 4, 4, 87, 77, 48, 158, 158, 38,
		91, 4, 4, 93, 123, 21, 72, 71, 72, 72, 72, 72, 3, 91, 4, 4, 4, 4, 4, 4, 4, 4, 114, 4, 64, 4, 93, 28, 29, 38,
		91, 96, 4, 93, 111, 83, 11, 41, 42, 42, 42, 43, 13, 91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 113, 82, 82, 83,
		91, 96, 96, 4, 4, 93, 11, 61, 62, 62, 62, 63, 13, 101, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 137, 4, 4, 93,
		91, 4, 114, 4, 4, 93, 21, 22, 22, 22, 22, 22, 23, 31, 101, 4, 4, 138, 136, 4, 4, 96, 132, 4, 4, 137, 4, 4, 4, 93,
		91, 4, 4, 4, 4, 113, 82, 82, 82, 82, 82, 82, 83, 32, 32, 91, 4, 138, 136, 4, 4, 4, 4, 4, 4, 4, 4, 137, 4, 93,
		91, 4, 114, 52, 4, 4, 4, 4, 4, 14, 4, 114, 93, 31, 32, 101, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 93,
		91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 83, 32, 32, 91, 4, 4, 4, 4, 4, 52, 4, 104, 114, 104, 4, 4, 93,
		91, 4, 4, 4, 4, 4, 114, 114, 4, 4, 4, 4, 4, 93, 31, 32, 101, 4, 114, 4, 4, 4, 4, 4, 62, 62, 62, 4, 4, 93,
		91, 4, 4, 4, 4, 96, 4, 4, 4, 96, 4, 4, 4, 4, 83, 32, 32, 91, 4, 4, 14, 4, 4, 4, 43, 112, 41, 4, 4, 93,
		91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 92, 93, 31, 32, 91, 4, 113, 92, 4, 4, 4, 132, 42, 4, 4, 4, 93,
		101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 113, 93, 32, 32, 91, 93, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 103
	};

	backImg = new Image("Resources/GroundTiles.bmp", 64, 64, 16, MapData, 30, 20);

	// cria cena
	infoBox   = new Sprite("Resources/InfoBox.png");
	keyMap    = new Sprite("Resources/Keymap.png");
	backg     = new Sprite(backImg);
	maxWidth  = float(backg->Width());
	maxHeight = float(backg->Height());

	// cria fontes para exibição de texto
	font = new Font("Resources/Tahoma14.png");
	font->Spacing("Resources/Tahoma14.dat");
	bold = new Font("Resources/Tahoma14b.png");
	bold->Spacing("Resources/Tahoma14b.dat");

	// calcula posição para manter viewport centralizada
	float deltaX = (maxWidth - window->Width()) / 2.0f;
	float deltaY = (maxHeight - window->Height()) / 2.0f;

	// inicializa viewport para o centro do background
	viewport.left = 0.0f + deltaX;
	viewport.right = viewport.left + window->Width();
	viewport.top = 0.0f + deltaY;
	viewport.bottom = viewport.top + window->Height();

	// inicializa velocidade de rolamento da tela
	scrollSpeed = 8;
}

// ------------------------------------------------------------------------------

void TiledScroll::Update()
{
	// sai com o pressionamento da tecla ESC
	window->CloseOnEscape();

	// deslocamento padrão
	float delta = 50 * gameTime;

	// movimenta viewport
	if (window->KeyDown(VK_LEFT))
	{
		viewport.left -= scrollSpeed * delta;
		viewport.right -= scrollSpeed * delta;

		if (viewport.left < 0)
		{
			viewport.left = 0;
			viewport.right = float(window->Width());
		}
	}

	if (window->KeyDown(VK_RIGHT))
	{
		viewport.left += scrollSpeed * delta;
		viewport.right += scrollSpeed * delta;

		if (viewport.right > (maxWidth))
		{
			viewport.left = maxWidth - window->Width();
			viewport.right = maxWidth;
		}
	}

	if (window->KeyDown(VK_UP))
	{
		viewport.top -= scrollSpeed * delta;
		viewport.bottom -= scrollSpeed * delta;

		if (viewport.top < 0)
		{
			viewport.top = 0;
			viewport.bottom = float(window->Height());
		}
	}

	if (window->KeyDown(VK_DOWN))
	{
		viewport.top += scrollSpeed * delta;
		viewport.bottom += scrollSpeed * delta;

		if (viewport.bottom > maxHeight)
		{
			viewport.top = maxHeight - window->Height();
			viewport.bottom = maxHeight;
		}
	}
} 

// ------------------------------------------------------------------------------

void TiledScroll::Draw()
{
	// desenha pano de fundo
	RECT region = { long(viewport.left), long(viewport.top), long(viewport.right), long(viewport.bottom) };
	backg->Draw(window->CenterX(), window->CenterY(), 1.0f, 1.0f, 0.0f, Color(1,1,1,1), region);
	
	// desenha elementos da interface
	infoBox->Draw(150, 100, 0.2f);
	keyMap->Draw(window->CenterX(), window->Height() - 16.0f, 0.2f);
	
	// desenha texto
	text.str("");
	text << "Tiled Map";
	bold->Draw(60, 65, text.str());

	text.str("");
	text << "Janela: " << window->Width() << " x " << window->Height();
	font->Draw(60, 105, text.str());

	text.str("");
	text << "Background: " << maxWidth << " x " << maxHeight;
	font->Draw(60, 125, text.str());
	
	text.str("");
	text << "Viewport: (" << region.left << "," << region.top << ") a (" << region.right << "," << region.bottom << ")";
	font->Draw(60, 145, text.str());
	
	text.str("");
	text << "Use as setas para mover a Viewport";
	font->Draw(window->CenterX() - 82.0f, window->Height() - 7.0f, text.str());
} 

// ------------------------------------------------------------------------------

void TiledScroll::Finalize()
{
	delete infoBox;
	delete keyMap;
	delete backImg;
	delete backg;
	delete font;
	delete bold;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Engine * engine = new Engine();

	// configura janela
	engine->window->Mode(WINDOWED);
	engine->window->Size(1152, 648);
	engine->window->Color(0, 0, 0);
	engine->window->Title("Tiled Map");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);
	//engine->window->HideCursor(true);

	// configura dispositivo gráfico
	//engine->graphics->VSync(true);

	// inicia o jogo
	engine->Start(new TiledScroll());

	delete engine;
	return 0;
}

// ----------------------------------------------------------------------------

