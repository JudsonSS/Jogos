/**********************************************************************************
// Transform2D (Código Fonte)
//
// Criação:		11 Nov 2011
// Atualização:	15 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Teste de transformações - Translação, Rotação e Escala
//
**********************************************************************************/

#include "Engine.h"
#include "Transform2D.h"

// ------------------------------------------------------------------------------

void Transform2D::Init()
{
	// inicializa controle
	gameCtrl = new Controller();
	controllerOn = gameCtrl->Initialize();

	// cria fontes para exibição de texto
	sysFont = new Font("Resources/Tahoma14.png");
	sysFont->Spacing("Resources/Tahoma14.dat");

	// carrega painéis e pano de fundo
	backg = new Sprite("Resources/Kamikaze.jpg");
	infoBox = new Sprite("Resources/InfoBox.png");
	keyMap = new Sprite("Resources/KeyMap.png");
	
	// cria avião
	plane = new Plane();
	plane->MoveTo(window->CenterX(), window->CenterY());

	// calcula proporção entre a janela e o pano de fundo
	float horzScale = window->Width() / 1920.0f;
	float vertScale = window->Height() / 1080.0f;

	// define escala para o pano de fundo
	backgScale = horzScale > vertScale ? horzScale : vertScale;
}

// ------------------------------------------------------------------------------

void Transform2D::Update()
{
	window->CloseOnEscape();

	// deslocamento padrão
	float delta = 250 * gameTime;

	// -----------------
	// Teclado
	// -----------------
	if (window->KeyDown(VK_RIGHT))
		plane->Translate(delta, 0);

	if (window->KeyDown(VK_LEFT))
		plane->Translate(-delta, 0);

	if (window->KeyDown(VK_UP))
		plane->Translate(0, -delta);

	if (window->KeyDown(VK_DOWN))
		plane->Translate(0, delta);

	if (window->KeyDown('S'))
		plane->Scale(1 + 0.005f * delta);

	if (window->KeyDown('A'))
		plane->Scale(1 - 0.005f * delta);

	if (window->KeyDown('Z'))
		plane->Rotate(-0.5f * delta);

	if (window->KeyDown('X'))
		plane->Rotate(0.5f * delta);

	if (window->KeyDown('R'))
	{
		plane->MoveTo(window->CenterX(), window->CenterY());
		plane->rotation = 0;
		plane->scale = 1;
	}

	// -----------------
	// Controle
	// -----------------

	if (controllerOn)
	{
		gameCtrl->UpdateState();

		plane->Translate(gameCtrl->Axis(AxisX) * gameTime, gameCtrl->Axis(AxisY) * gameTime);
		plane->Scale(1 - gameCtrl->Axis(AxisZ) * 0.001f * gameTime);
		plane->Rotate(delta * gameCtrl->Axis(AxisRX) * 0.001f);
		plane->Rotate(-delta * gameCtrl->Axis(AxisRY) * 0.001f);

		if (gameCtrl->ButtonCtrl(START))
		{
			plane->MoveTo(window->CenterX(), window->CenterY());
			plane->rotation = 0;
			plane->scale = 1;
		}

		switch (gameCtrl->Dpad(DPAD))
		{
		case 0:
			plane->Translate(0.0f, -delta);    // para cima
			break;
		case 4500:
			plane->Translate(delta, -delta);   // para cima e direita
			break;
		case 9000:
			plane->Translate(delta, 0.0f);     // para direita
			break;
		case 13500:
			plane->Translate(delta, delta);    // para baixo e direita
			break;
		case 18000:
			plane->Translate(0.0f, delta);     // para baixo
			break;
		case 22500:
			plane->Translate(-delta, delta);   // para baixo e esquerda
			break;
		case 27000:
			plane->Translate(-delta, 0.0f);   // para esquerda
			break;
		case 31500:
			plane->Translate(-delta, -delta);  // para cima e esquerda
			break;
		}
	}
} 

// ------------------------------------------------------------------------------

void Transform2D::Draw()
{
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, backgScale);
	keyMap->Draw(window->CenterX(), window->Height() - 16.0f, Layer::MIDFRONT);
	infoBox->Draw(120, 100, Layer::MIDFRONT);
	plane->Draw();

	Color textColor { 0.65f, 0.65f, 0.65f, 1.0f };

	text.str("");
	text << "Transformações 2D";
	sysFont->Draw(45, 64, text.str(), textColor);

	text.str("");
	text << "Posição do avião: " << int(plane->X()) << " x " << int(plane->Y());
	sysFont->Draw(45, 104, text.str(), textColor);

	text.str("");
	text << "Tamanho do avião: " << int(plane->Width() * plane->scale) << " x " << int(plane->Height() * plane->scale);
	sysFont->Draw(45, 124, text.str(), textColor);

	text.str("");
	text << "Ângulo de rotação: " << int(plane->rotation);
	sysFont->Draw(45, 144, text.str(), textColor);

	if (controllerOn)
	{
		text.str("");
		text << "LT | RT    Escala         LStick     Translação          Rotação      RStick      Reiniciar      Start";
		sysFont->Draw(window->CenterX() - 234.0f, window->Height() - 6.0f, text.str(), textColor);
	}
	else
	{
		text.str("");
		text << "A | S      Escala         Setas     Translação           Rotação      Z | X       Reiniciar        R";
		sysFont->Draw(window->CenterX() - 228.0f, window->Height() - 6.0f, text.str(), textColor);
	}
} 

// ------------------------------------------------------------------------------

void Transform2D::Finalize()
{
	delete backg;
	delete keyMap;
	delete infoBox;
	delete plane;
	delete gameCtrl;
	delete sysFont;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Engine * engine = new Engine();

	// configura janela
	engine->window->Mode(WINDOWED);
	engine->window->Size(1200, 640);
	engine->window->Color(0, 0, 0);
	engine->window->Title("Transform 2D");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	// configura dispositivo gráfico
	//engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new Transform2D());

	delete engine;
	return status;
}

// ----------------------------------------------------------------------------

