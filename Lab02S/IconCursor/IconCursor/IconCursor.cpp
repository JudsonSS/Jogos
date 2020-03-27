/**********************************************************************************
// IconCursor
// 
// Criação:		06 Mai 2011
// Atualização:	30 Abr 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	O exemplo mostra como personalizar o ícone/cursor da janela e cria 
//              variáveis globais para configurar facilmente o tamanho e o modo
//              da janela (tela cheia ou em janela).
//
**********************************************************************************/

// inclui tipos básicos e funções da API Win32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>	// inclui funções do windows
#include <windowsx.h>	// inclui funções extras do windows (como GetWindowStyle)
#include "Resources.h"  // definições dos recursos utilizados

// protótipo do procedimento da janela
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

// -----------------------------------------------------------------------
// constantes, variáveis e funções globais

int WindowWidth = 960;
int WindowHeight = 540;
bool FullScreen = false;

HWND hwnd;

// -----------------------------------------------------------------------

// programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	MSG          msg;
	WNDCLASS     wndclass;

	// definindo uma classe de janela chamada "GameWindow" 
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "GameWindow";

	// registrando "GameWindow"
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, "Erro na criação da janela!", "Game", MB_ICONERROR);
		return 0;
	}

	int WindowStyle = WS_OVERLAPPED | WS_SYSMENU;

	// tela cheia ou janela
	if (FullScreen)
	{
		WindowWidth = GetSystemMetrics(SM_CXSCREEN);
		WindowHeight = GetSystemMetrics(SM_CYSCREEN);
		WindowStyle = WS_POPUP;
	}

	// criando uma janela baseada na classe "GameWindow"
	// necessário usar CreateWindowEx para usar AdjustWindowRectEx
	hwnd = CreateWindowEx(
		NULL,							// estilos extras
		"GameWindow",					// nome da "window class"
		"Game",							// título da janela
		WindowStyle,					// estilo da janela
		CW_USEDEFAULT,					// posição x inicial
		CW_USEDEFAULT,					// posição y inicial
		WindowWidth,					// largura da janela
		WindowHeight,					// altura da janela
		NULL,							// identificador do objeto pai
		NULL,							// identificador do menu
		hInstance,						// identificador da aplicação
		NULL);							// parâmetros de criação

	if (!FullScreen)
	{
		// retângulo com o tamanho da área cliente desejada
		RECT winRect = { 0, 0, WindowWidth, WindowHeight };

		// ajuste do tamanho da janela
		AdjustWindowRectEx(&winRect,
			GetWindowStyle(hwnd),
			GetMenu(hwnd) != NULL,
			GetWindowExStyle(hwnd));

		// atualiza posição da janela
		int windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((winRect.right - winRect.left) / 2);
		int windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((winRect.bottom - winRect.top) / 2);

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

	// tratamento de mensagens destinadas a janela da aplicação
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// fim do programa
	return msg.wParam;
}

// -----------------------------------------------------------------------

// procedimento da janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

// -----------------------------------------------------------------------