/**********************************************************************************
// BackScroll (Código Fonte)
// 
// Criação:		22 Out 2012
// Atualização:	14 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Desenhando e movimentando um background maior que a janela
//
**********************************************************************************/

#include "Engine.h"
#include "BackScroll.h"

// ------------------------------------------------------------------------------

void BackScroll::Init() 
{
	// cria cena
	infoBox = new Sprite("Resources/InfoBox.png");
	keyMap  = new Sprite("Resources/Keymap.png");

	backg     = new Sprite("Resources/Backg.jpg");
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

void BackScroll::Update()
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

		if (viewport.right > maxWidth)
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

void BackScroll::Draw()
{
	// desenha o pano de fundo
	RECT region = {long(viewport.left), long(viewport.top), long(viewport.right), long(viewport.bottom)};
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1.0f, 0.0f, Color(1,1,1,1), region);
	
	// desenha os elementos da interface
	infoBox->Draw(150, 100, Layer::FRONT);
	keyMap->Draw(window->CenterX(), window->Height() - 16.0f, Layer::FRONT);
	
	// desenha os textos
	text.str("");
	text << "Background Scrolling";
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

void BackScroll::Finalize()
{
	delete infoBox;
	delete keyMap;
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
	engine->window->Title("Background Scrolling");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);
	//engine->window->HideCursor(true);

	// configura dispositivo gráfico
	//engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new BackScroll());

	delete engine;
	return status;
}

// ----------------------------------------------------------------------------

