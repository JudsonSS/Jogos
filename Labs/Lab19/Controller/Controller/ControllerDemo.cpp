/**********************************************************************************
// ControllerDemo (Código Fonte)
//
// Criação:		09 Nov 2011
// Atualização:	11 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Exemplo de uso da classe Controller
//
**********************************************************************************/

#include "Engine.h"
#include "ControllerDemo.h"

// ------------------------------------------------------------------------------

void ControllerDemo::Init()
{
	// cria gerenciador de controles
	gameCtrl = new Controller();

	// tenta inicializar um controle do xbox
	xboxOn = gameCtrl->XboxInitialize(xboxPlayer);
	
	// se falhar, tenta inicializar um controle qualquer
	if (!xboxOn)
		controllerOn = gameCtrl->Initialize();

	// cria fontes para exibição de texto
	sysFont = new Font("Resources/Tahoma14.png");
	sysFont->Spacing("Resources/Tahoma14.dat");
	gameFont = new Font("Resources/Agency30.png");
	gameFont->Spacing("Resources/Agency30.dat");

	// carrega sprites
	backg = new Sprite("Resources/Background.jpg");
	overlay = new Sprite("Resources/Overlay.png");
	xboxOver = new Sprite("Resources/XboxOverlay.png");
	xbox360 = new Sprite("Resources/Xbox360.png");
	box = new Sprite("Resources/Box.png");

	A = new Sprite("Resources/A.png");
	B = new Sprite("Resources/B.png");
	X = new Sprite("Resources/X.png");
	Y = new Sprite("Resources/Y.png");

	RB = new Sprite("Resources/RB.png");
	LB = new Sprite("Resources/LB.png");
	RT = new Sprite("Resources/RT.png");
	LT = new Sprite("Resources/LT.png");

	Start = new Sprite("Resources/Start.png");
	Back = new Sprite("Resources/Back.png");
	LThumb = new Sprite("Resources/Thumb.png");
	RThumb = new Sprite("Resources/Thumb.png");

	LStick = new Sprite("Resources/Stick.png");
	RStick = new Sprite("Resources/Stick.png");
	DpadU = new Sprite("Resources/DpadU.png");
	DpadD = new Sprite("Resources/DpadD.png");
	DpadL = new Sprite("Resources/DpadL.png");
	DpadR = new Sprite("Resources/DpadR.png");

	P1 = new Sprite("Resources/P1.png");
	P2 = new Sprite("Resources/P2.png");
	P3 = new Sprite("Resources/P3.png");
	P4 = new Sprite("Resources/P4.png");

	// posição inicial da caixa
	boxX = 614;
	boxY = 286;
}

// ------------------------------------------------------------------------------

void ControllerDemo::Update()
{
	window->CloseOnEscape();

	// alterna entre DirectInput e XInput
	if (window->KeyCtrl(VK_SPACE))
	{
		if (controllerOn)
		{
			xboxOn = gameCtrl->XboxInitialize(xboxPlayer);
			controllerOn = false;
		}
		else
		{
			xboxOn = false;
			controllerOn = gameCtrl->Initialize();
		}
	}

	// --------------------------
	// Controle
	// --------------------------
	if (controllerOn)
	{
		// seleciona próximo controle (Page Down)
		if (window->KeyCtrl(VK_NEXT))
			gameCtrl->DeviceNext();

		// seleciona controle anterior (Page Up)
		if (window->KeyCtrl(VK_PRIOR))
			gameCtrl->DevicePrev();

		gameCtrl->UpdateState();

		// move caixa com analógicos
		boxX += gameCtrl->Axis(AxisX) * gameTime;
		boxY += gameCtrl->Axis(AxisY) * gameTime;
		boxX += gameCtrl->Axis(AxisRX) * gameTime;
		boxY += gameCtrl->Axis(AxisRY) * gameTime;
				
		// move caixa com gatilhos
		boxX += -gameCtrl->Axis(AxisZ) * gameTime;
		boxX += -gameCtrl->Axis(AxisRZ) * gameTime;

		// move caixa com Dpad
		float delta = 300 * gameTime;
		switch (gameCtrl->Dpad())
		{
		case 0:
			boxX += 0.0f;		// para cima
			boxY += -delta;		
			break;
		case 4500:
			boxX += delta;		// para cima e direita
			boxY += -delta;
			break;
		case 9000:
			boxX += delta;		// para direita
			boxY += 0.0f;
			break;
		case 13500:
			boxX += delta;		// para baixo e direita
			boxY += delta;    
			break;
		case 18000:
			boxX += 0.0f;		// para baixo
			boxY += delta;
			break;
		case 22500:
			boxX += -delta;		// para baixo e esquerda
			boxY += delta;
			break;
		case 27000:
			boxX += -delta;		// para esquerda
			boxY += 0.0f;
			break;
		case 31500:
			boxX += -delta;		// para esquerda e para cima
			boxY += -delta;
			break;
		}

		// move caixa com os botões dos ombros
		if (gameCtrl->ButtonDown(4))
		{
			// para esquerda
			boxX += -delta;		
			boxY += 0.0f;
		}
		if (gameCtrl->ButtonDown(5))
		{
			// para direita
			boxX += delta;
			boxY += 0.0f;
		}

		// restaura posição inicial da caixa com Start ou Back
		if (gameCtrl->ButtonDown(6) | gameCtrl->ButtonDown(7))
		{
			boxX = 614;
			boxY = 286;
		}

		// mantém caixa 50x50 dentro das coordenadas (499, 171) a (730, 401)
		if (boxX - 25.0f < 499)
			boxX = 524.0f;
		if (boxX + 25.0f > 730)
			boxX = 705.0f;
		if (boxY - 25.0f < 171)
			boxY = 196.0f;
		if (boxY + 25.0f > 401)
			boxY = 376.0f;
	}
	else
	{
		// --------------------------
		// Controle do Xbox
		// --------------------------
		if (xboxOn)
		{
			// seleciona próximo controle (Page Down)
			if (window->KeyCtrl(VK_NEXT))
			{
				uint nextPlayer = (xboxPlayer + 1) % 4;
				
				// se controle para próximo jogador está conectado				
				if (gameCtrl->XboxUpdateState(nextPlayer))
					xboxPlayer = nextPlayer;
			}
			// seleciona controle anterior (Page Up)
			if (window->KeyCtrl(VK_PRIOR))
			{
				uint prevPlayer = xboxPlayer == 0 ? 3 : xboxPlayer - 1;

				// se controle para jogador anterior está conectado	
				if (gameCtrl->XboxUpdateState(prevPlayer))
					xboxPlayer = prevPlayer;
			}

			// atualiza estado do controle
			gameCtrl->XboxUpdateState(xboxPlayer);

			if (gameCtrl->XboxButton(ButtonBack))
			{
				// parada de segurança da vibração
				gameCtrl->XboxVibrate(xboxPlayer, 0, 0);
			}
			else
			{
				// vibra com os valores dos gatilhos
				gameCtrl->XboxVibrate(xboxPlayer, gameCtrl->XboxTrigger(LeftTrigger) * 257, gameCtrl->XboxTrigger(RightTrigger) * 257);
			}			
		}
	}
} 

// ------------------------------------------------------------------------------

void ControllerDemo::Draw()
{
	// desenha pano de fundo
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

	// --------------------------
	// Controle
	// --------------------------

	// exibe texto com dados do controle conectado
	if (controllerOn)
	{
		// desenha pano de fundo sobreposto
		overlay->Draw(window->CenterX(), window->CenterY(), Layer::MIDBACK);
		
		// desenha caixa
		box->Draw(boxX, boxY, Layer::MIDDLE);

		// mostra nome do dispositivo
		text.str("");
		text << gameCtrl->DeviceName()->c_str();
		gameFont->Draw(240, 100, text.str(), Color(0.28f, 0.28f, 0.28f, 1.0f));

		// pega lista de componentes do dispositivo
		list<JoyPart> joyParts = gameCtrl->DeviceParts();
		float posY = 175.0f;

		int bt = 0;
		int pov = 0;

		// mostra nome e valor de cada componente
		for (const auto & i : joyParts)
		{
			text.str("");

			if (i.guid == GUID_XAxis)
				text << i.name << ": " << gameCtrl->Axis(AxisX);
			else if (i.guid == GUID_YAxis)
				text << i.name << ": " << gameCtrl->Axis(AxisY);
			else if (i.guid == GUID_ZAxis)
				text << i.name << ": " << gameCtrl->Axis(AxisZ);
			else if (i.guid == GUID_RxAxis)
				text << i.name << ": " << gameCtrl->Axis(AxisRX);
			else if (i.guid == GUID_RyAxis)
				text << i.name << ": " << gameCtrl->Axis(AxisRY);
			else if (i.guid == GUID_RzAxis)
				text << i.name << ": " << gameCtrl->Axis(AxisRZ);
			else if (i.guid == GUID_Button)
				text << i.name << ": " << gameCtrl->ButtonDown(bt++);
			else if (i.guid == GUID_POV)
				text << i.name << ": " << gameCtrl->Dpad(pov++);
			else if (i.guid == GUID_Slider)
				text << i.name << ": " << gameCtrl->Slider(0);
			else if (i.guid == GUID_Unknown)
				text << "Controller Unknown";
			else if (i.guid == GUID_Key)
				text << "Controller Key";

			sysFont->Draw(242.0f, posY, text.str(), Color(0.28f, 0.28f, 0.28f, 1.0f));
			posY = posY + 20.0f;
		}
	}
	else
	{
		// --------------------------
		// Controle do Xbox
		// --------------------------

		if (xboxOn)
		{
			// desenha controle do Xbox 360
			xbox360->Draw(window->CenterX(), window->CenterY(), Layer::MIDBACK);

			// desenha pano de fundo sobreposto
			xboxOver->Draw(window->CenterX(), window->CenterY(), Layer::MIDDLE);

			// desenha indicação do controle ativo
			switch (xboxPlayer)
			{
			case PLAYER1: P1->Draw(window->CenterX(), window->CenterY(), Layer::MIDFRONT); break;
			case PLAYER2: P2->Draw(window->CenterX(), window->CenterY(), Layer::MIDFRONT); break;
			case PLAYER3: P3->Draw(window->CenterX(), window->CenterY(), Layer::MIDFRONT); break;
			case PLAYER4: P4->Draw(window->CenterX(), window->CenterY(), Layer::MIDFRONT); break;
			}

			// desenha valores dos eixos e gatilhos
			text.str("");
			text << gameCtrl->XboxTrigger(LeftTrigger);
			int length = int(text.tellp());
			gameFont->Draw(220 - (5.0f * length), 148.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

			text.str("");
			text << gameCtrl->XboxTrigger(RightTrigger);
			length = int(text.tellp());
			gameFont->Draw(775 - (5.0f * length), 148.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

			text.str("");
			text << gameCtrl->XboxAnalog(ThumbLX);
			length = int(text.tellp());
			gameFont->Draw(125 - (5.0f * length), 425.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

			text.str("");
			text << gameCtrl->XboxAnalog(ThumbLY);
			length = int(text.tellp());
			gameFont->Draw(218 - (5.0f * length), 489.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

			text.str("");
			text << gameCtrl->XboxAnalog(ThumbRX);
			length = int(text.tellp());
			gameFont->Draw(868 - (5.0f * length), 425.0f, text.str(), Color(0.28f, 0.28f, 0.28f, 1.0f));

			text.str("");
			text << gameCtrl->XboxAnalog(ThumbRY);
			length = int(text.tellp());
			gameFont->Draw(775 - (5.0f * length), 489.0f, text.str(), Color(0.25f, 0.25f, 0.25f, 1.0f));

			// desenha indicações de botões pressionados
			if (gameCtrl->XboxButton(ButtonA))
				A->Draw(642, 305);
			if (gameCtrl->XboxButton(ButtonB))
				B->Draw(689, 267);
			if (gameCtrl->XboxButton(ButtonX))
				X->Draw(601, 270);
			if (gameCtrl->XboxButton(ButtonY))
				Y->Draw(647, 233);
			if (gameCtrl->XboxButton(RightBumper))
				RB->Draw(646, 171);
			if (gameCtrl->XboxButton(LeftBumper))
				LB->Draw(315, 171);
			if (gameCtrl->XboxTrigger(RightTrigger))
				RT->Draw(632, 129);
			if (gameCtrl->XboxTrigger(LeftTrigger))
				LT->Draw(331, 129);
			if (gameCtrl->XboxButton(ButtonStart))
				Start->Draw(541, 272);
			if (gameCtrl->XboxButton(ButtonBack))
				Back->Draw(422, 272);

			// captura valores dos analógicos na faixa de -15 a 15
			float lx = gameCtrl->XboxAnalog(ThumbLX) / 2184.46f;
			float ly = gameCtrl->XboxAnalog(ThumbLY) / 2184.46f;
			float rx = gameCtrl->XboxAnalog(ThumbRX) / 2184.46f;
			float ry = gameCtrl->XboxAnalog(ThumbRY) / 2184.46f;

			// desenha analógicos de acordo com suas posições
			LStick->Draw(315 + lx, 284 - ly);
			RStick->Draw(556 + rx, 357 - ry);

			// desenha indicações do pressionamento dos analógicos
			if (gameCtrl->XboxButton(LeftThumb))
				LThumb->Draw(315 + lx, 284 - ly, Layer::MIDFRONT);
			if (gameCtrl->XboxButton(RightThumb))
				RThumb->Draw(556 + rx, 357 - ry, Layer::MIDFRONT);

			// desenha indicações de pressionamentos do Dpad
			if (gameCtrl->XboxButton(DpadUp))
				DpadU->Draw(398, 331);
			if (gameCtrl->XboxButton(DpadDown))
				DpadD->Draw(399, 381);
			if (gameCtrl->XboxButton(DpadLeft))
				DpadL->Draw(368, 356);
			if (gameCtrl->XboxButton(DpadRight))
				DpadR->Draw(429, 358);

			// mostra todos os botões do controle com <ENTER>
			if (window->KeyDown(VK_RETURN))
			{
				A->Draw(642, 305);
				B->Draw(689, 267);
				X->Draw(601, 270);
				Y->Draw(647, 233);
				RB->Draw(646, 171);
				LB->Draw(315, 171);
				RT->Draw(632, 129);
				LT->Draw(331, 129);
				Start->Draw(541, 272);
				Back->Draw(422, 272);

				float lx = gameCtrl->XboxAnalog(ThumbLX) / 2184.46f; 
				float ly = gameCtrl->XboxAnalog(ThumbLY) / 2184.46f; 
				float rx = gameCtrl->XboxAnalog(ThumbRX) / 2184.46f; 
				float ry = gameCtrl->XboxAnalog(ThumbRY) / 2184.46f; 

				LThumb->Draw(315 + lx, 284 - ly, Layer::MIDFRONT);
				RThumb->Draw(556 + rx, 357 - ry, Layer::MIDFRONT);
				DpadU->Draw(398, 331);
				DpadD->Draw(399, 381);
				DpadL->Draw(368, 356);
				DpadR->Draw(429, 358);
			}
		}
		else
		{
			// ---------------------------------
			// Controle Não Compatível com Xbox
			// ---------------------------------

			// desenha controle do Xbox 360
			xbox360->Draw(window->CenterX(), window->CenterY(), Layer::MIDBACK);

			// desenha mensagem de incompatibilidade 
			gameFont->Draw(360.0f, 480.0f, "Controle compatível não encontrado", Color(0.25f, 0.25f, 0.25f, 1.0f));
		}
	}
} 

// ------------------------------------------------------------------------------

void ControllerDemo::Finalize()
{
	// libera sprites
	delete P1;
	delete P2;
	delete P3;
	delete P4;

	delete A;
	delete B;
	delete X;
	delete Y;

	delete RB;
	delete LB;
	delete RT;
	delete LT;

	delete Start;
	delete Back;
	delete LThumb;
	delete RThumb;
	delete LStick;
	delete RStick;

	delete DpadR;
	delete DpadL;
	delete DpadU;
	delete DpadD;

	delete backg;
	delete overlay;
	delete xboxOver;
	delete xbox360;
	delete box;

	// libera fontes
	delete gameFont;
	delete sysFont;
	
	// libera controles
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
	engine->window->Title("Controller");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	// configura dispositivo gráfico
	engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new ControllerDemo());

	delete engine;
	return status;
}

// ----------------------------------------------------------------------------

