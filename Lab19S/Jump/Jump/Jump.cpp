/**********************************************************************************
// Jump (Código Fonte)
//
// Criação:		10 Jul 2019
// Atualização:	11 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Exercício de uso da classe Controller
//
**********************************************************************************/

#include "Engine.h"
#include "Jump.h"

// ------------------------------------------------------------------------------

void Jump::Init()
{
	// cria e inicializa controle
	gameCtrl = new Controller();
	gameCtrl->XboxInitialize(PLAYER1);

	// carrega sprites e cria animação
	braidSet = new TileSet("Resources/Braid.png", 120, 140, 9, 9);
	anim = new Animation(braidSet, 0.250f, false);
	dot = new Sprite("Resources/Dot.png");

	// posição inicial do personagem
	posX = window->CenterX() - 100.0f;
	posY = window->CenterY() + 50.0f;
}

// ------------------------------------------------------------------------------

void Jump::Update()
{
	window->CloseOnEscape();

	// atualiza estado do controle
	gameCtrl->XboxUpdateState();

	// se personagem está pulando
	if (jumping)
	{
		if (dotTimer.Elapsed(0.1f))
		{
			// adiciona coordenada atual no rastro
			trail.insert(trail.end(), { posX - 40, posY + 70 });
			dotTimer.Reset();
		}

		if (jumpTimer.Elapsed(2.5f))
		{
			// restaura personagem ao estado inicial
			jumping = false;
			posX = oldX;
			posY = oldY;
			anim->Restart();
			trail.clear();
		}
		else if (jumpTimer.Elapsed(2.0f))
		{
			// finaliza pulo
			velX = 0;
			velY = 0;
		}
		else
		{
			anim->NextFrame();

			if (jumpTimer.Elapsed(1.0f))
			{
				// descida
				velY += 100.0f * gameTime;
				velX -= 100.0f * gameTime;
			}
			else
			{
				// subida
				velY += 100.0f * gameTime;
				velX += 100.0f * gameTime;
			}
		}
	}
	else
	{
		if (window->KeyCtrl(VK_SPACE) || gameCtrl->XboxButton(ButtonA))
		{
			// inicia pulo
			velX = 100;
			velY = -100;
			
			// adiciona coordenada atual no rastro
			trail.insert(trail.end(), { posX - 40, posY + 70 });
			
			// salva posição atual
			oldX = posX;
			oldY = posY;

			// inicia temporizadores
			jumpTimer.Start();
			dotTimer.Start();
			jumping = true;
		}

		posX += gameCtrl->XboxAnalog(ThumbLX) / 200 * gameTime;
		posY -= gameCtrl->XboxAnalog(ThumbLY) / 200 * gameTime;

		if (window->KeyDown(VK_LEFT))
			posX -= 200 * gameTime;
		if (window->KeyDown(VK_RIGHT))
			posX += 200 * gameTime;
		if (window->KeyDown(VK_UP))
			posY -= 200 * gameTime;
		if (window->KeyDown(VK_DOWN))
			posY += 200 * gameTime;
	}
	
	// atualiza posição do personagem 
	posX += velX * gameTime;
	posY += velY * gameTime;
} 

// ------------------------------------------------------------------------------

void Jump::Draw()
{
	// desenha personagem
	anim->Draw(posX, posY);

	// desenha rastro
	for (const auto& [x, y] : trail)
		dot->Draw(x, y);
} 

// ------------------------------------------------------------------------------

void Jump::Finalize()
{
	delete dot;
	delete anim;
	delete braidSet;	
	delete gameCtrl;
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
	engine->window->Color(20, 20, 20);
	engine->window->Title("Jump");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	// configura dispositivo gráfico
	//engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new Jump());

	delete engine;
	return status;
}

// ----------------------------------------------------------------------------

