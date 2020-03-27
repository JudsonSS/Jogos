/**********************************************************************************
// WindowPlot
// 
// Criação:		19 Ago 2011
// Atualização:	09 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Exemplo de game loop. 
//              Desenha pixels aleatoriamente na janela.
//
**********************************************************************************/

#include <windows.h>	// funções do windows
#include <windowsx.h>	// extensões do windows
#include "Resources.h"  // definições dos recursos utilizados
#include <random>		// números aleatórios

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

// protótipo do procedimento da janela
LRESULT CALLBACK WinProc (HWND, UINT, WPARAM, LPARAM);

// -----------------------------------------------------------------------
// constantes, variáveis e funções globais

int windowWidth = 960;		// largura da janela
int windowHeight = 540;		// altura da janela
bool fullScreen = false;	// tela cheia ou modo janela

bool vkKeys[256] = { 0 };	// estado das teclas do teclado

HWND	 hwnd;				// id da janela
HDC      hdc;				// id do contexto do dispositivo
int      x, y;				// posição do pixel
COLORREF color;				// cor do pixel

random_device rd;			// gerador aleatório não determinístico 
mt19937 mt;					// gerador aleatório Mersenne Twister

// distribuições uniformes para cor, largura e altura
uniform_int_distribution<int> randColor(0, 255);
uniform_int_distribution<int> randWidth(0, windowWidth-1);
uniform_int_distribution<int> randHeight(0, windowHeight-1);

// -----------------------------------------------------------------------
// funções do jogo

// inicializa o jogo alocando recursos
void GameInit()
{
	// pega o contexto do dispositivo gráfico
	hdc = GetDC(hwnd);
}

// atualiza a lógica do jogo
void GameUpdate()
{
	// sai do jogo com o pressionamento da tecla ESC
	if (vkKeys[VK_ESCAPE])
		PostMessage(hwnd, WM_DESTROY, 0, 0);

	// calcula a posição do próximo pixel
	x = randWidth(mt);
	y = randHeight(mt);

	// define a cor do próximo pixel
	color = RGB(randColor(mt), randColor(mt), randColor(mt));
}

// desenha o próximo quadro do jogo
void GameDraw()
{
	// desenha um pixel na posição e cor indicadas
	SetPixel(hdc, x, y, color);
}

// finaliza o jogo desalocando recursos
void GameFinalize()
{
	// libera o contexto do dispositivo gráfico
	ReleaseDC(hwnd, hdc);
}

// -----------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    MSG          msg;
    WNDCLASS     wndclass; 

	// Definindo uma classe de janela chamada "GameWindow" 
    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = WinProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = hInstance;
    wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wndclass.hCursor       = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
    wndclass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = "GameWindow";

	// Registrando "GameWindow"
    if (!RegisterClass (&wndclass))
    {
         MessageBox (NULL, "Erro na criação da janela!", "Game", MB_ICONERROR);
         return 0 ;
    }

	// inicialmente o estilo escolhido é em janela
	int windowStyle = WS_OVERLAPPED | WS_SYSMENU;

	// tela cheia ou janela
	if (fullScreen)
	{
		windowWidth  = GetSystemMetrics(SM_CXSCREEN);
		windowHeight = GetSystemMetrics(SM_CYSCREEN);
		windowStyle  = WS_POPUP;
	}

	// criando uma janela baseada na classe "GameWindow" 
    hwnd = CreateWindowEx(
			NULL,							// estilos extras
			"GameWindow",					// nome da "window class"
			"Game",							// título da janela
			windowStyle,					// estilo da janela
			CW_USEDEFAULT,					// posição x inicial
			CW_USEDEFAULT,					// posição y inicial
			windowWidth,					// largura da janela
			windowHeight,					// altura da janela
			NULL,							// identificador do objeto pai
			NULL,							// identificador do menu
			hInstance,						// identificador da aplicação
			NULL);							// parâmetros de criação

	if (!fullScreen)
	{
		// retângulo com o tamanho da área cliente desejada
		RECT winRect = {0, 0, windowWidth, windowHeight};

		// ajuste do tamanho da janela
		AdjustWindowRectEx(&winRect,
						   GetWindowStyle(hwnd),
						   GetMenu(hwnd) != NULL,
						   GetWindowExStyle(hwnd));

		// atualiza posição da janela
		int windowPosX = (GetSystemMetrics(SM_CXSCREEN)/2) - ((winRect.right - winRect.left)/2);
		int windowPosY = (GetSystemMetrics(SM_CYSCREEN)/2) - ((winRect.bottom - winRect.top)/2);

		// redimensiona janela com uma chamada a MoveWindow
		MoveWindow(
			hwnd,							// identificador da janela
			windowPosX,						// posição x
			windowPosY,						// posição y
			winRect.right - winRect.left,	// largura
			winRect.bottom - winRect.top,	// altura
			TRUE);							// repintar
	}

	// mostra e atualiza a janela
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

	GameInit();

	// laço principal do jogo
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GameUpdate();
			GameDraw();
		}
	} 
	while (msg.message != WM_QUIT);

	GameFinalize();


	// fim do programa
    return msg.wParam;
}

// -----------------------------------------------------------------------
// procedimento da janela

LRESULT CALLBACK WinProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// processa teclas pressionadas
	case WM_KEYDOWN:
		vkKeys[wParam] = true;
		return 0;

		// processa teclas liberadas
	case WM_KEYUP:
		vkKeys[wParam] = false;
		return 0;

		// janela foi fechada
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

// -----------------------------------------------------------------------