/**********************************************************************************
// WinLine
// 
// Criação:		06 Mar 2012
// Atualização:	14 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Ilustra utilização da classe Game com ícone e cursor 
//              personalizado. Desenha e movimenta uma linha dentro da tela
//              usando as funções MoveToEx e LineTo da GDI do Windows.
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Resources.h"
#include <random>

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

// ------------------------------------------------------------------------------

class WinLine : public Game
{
private:
	HDC hdc;
	int x1, y1;
	int x2, y2;
	int x1Vel, y1Vel;
	int x2Vel, y2Vel;

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};

// ------------------------------------------------------------------------------

void WinLine::Init() 
{
	hdc = GetDC(window->Id());

	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> randWidth(0, window->Width() - 1);
	uniform_int_distribution<int> randHeight(0, window->Height() - 1);

	x1 = randWidth(mt);
	y1 = randHeight(mt);
	x2 = randWidth(mt);
	y2 = randHeight(mt);

	x1Vel = 5;
	y1Vel = 5;
	x2Vel = 5;
	y2Vel = 5;
}

// ------------------------------------------------------------------------------

void WinLine::Update()
{
	window->CloseOnEscape();

	x1 += x1Vel;
	y1 += y1Vel;
	x2 += x2Vel;
	y2 += y2Vel;

	if (x1 >= window->Width())
	{
		x1 = window->Width() - 1;
		x1Vel = -x1Vel;
	}
	if (x2 >= window->Width())
	{
		x2 = window->Width() - 1;
		x2Vel = -x2Vel;
	}
	if (x1 < 0)
	{
		x1 = 0;
		x1Vel = -x1Vel;
	}
	if (x2 < 0)
	{
		x2 = 0;
		x2Vel = -x2Vel;
	}
	if (y1 >= window->Height())
	{
		y1 = window->Height() - 1;
		y1Vel = -y1Vel;
	}
	if (y2 >= window->Height())
	{
		y2 = window->Height() - 1;
		y2Vel = -y2Vel;
	}
	if (y1 < 0)
	{
		y1 = 0;
		y1Vel = -y1Vel;
	}
	if (y2 < 0)
	{
		y2 = 0;
		y2Vel = -y2Vel;
	}
} 

// ------------------------------------------------------------------------------

void WinLine::Draw()
{	
	// move e traça nova linha
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
} 

// ------------------------------------------------------------------------------

void WinLine::Finalize()
{
	ReleaseDC(window->Id(), hdc);
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, 
	                 _In_opt_ HINSTANCE hPrevInstance, 
	                 _In_ LPSTR lpCmdLine, 
	                 _In_ int nCmdShow)
{
	// cria motor e configura a janela
	Engine * engine = new Engine();
	engine->window->Mode(WINDOWED);
	engine->window->Size(960, 540);
	engine->window->Color(240, 240, 140);
	engine->window->Title("Window Line");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);
	
	// cria e inicia o jogo
	Game * game = new WinLine();
	engine->Start(game);	
}

// ----------------------------------------------------------------------------

