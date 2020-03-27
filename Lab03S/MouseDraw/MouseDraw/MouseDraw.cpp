/**********************************************************************************
// MouseDraw
// 
// Cria��o:		13 Abr 2014
// Atualiza��o:	07 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Demonstra como usar a Mouse para pintar pixels na tela.
//
**********************************************************************************/

// inclui tipos b�sicos e fun��es da API Win32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>    // inclui fun��es do windows
#include <windowsx.h>	// inclui fun��es extras do windows
#include "Resources.h"  // defini��es dos recursos utilizados

//--------------------------------------------------------------------------------
// constantes e vari�veis globais
int windowWidth = 960;					// largura da janela
int windowHeight = 540;					// altura da janela
bool fullScreen = false;				// tela cheia ou modo janela

const unsigned MaxInputLength = 64;		// tamanho da string
char msg[MaxInputLength] = { 0 };		// mensagem do sistema

int mouseX = 0, mouseY = 0;				// posi��o do mouse
bool mouseLB = false;					// bot�o esquerdo do mouse pressionado
bool mouseMB = false;					// bot�o do meio do mouse pressionado
bool mouseRB = false;					// bot�o direito do mouse pressionado

//--------------------------------------------------------------------------------

// prot�tipo do procedimento da janela
LRESULT CALLBACK WinProc (HWND, UINT, WPARAM, LPARAM);

//--------------------------------------------------------------------------------

// programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
     HWND         hwnd;        // identificador da janela
     MSG          msg;         // mensagem
     WNDCLASS     wndclass;    // classe da janela

	 // definindo uma classe de janela chamada "GameWindow" 
	 wndclass.style = CS_HREDRAW | CS_VREDRAW;
	 wndclass.lpfnWndProc = WinProc;
	 wndclass.cbClsExtra = 0;
	 wndclass.cbWndExtra = 0;
	 wndclass.hInstance = hInstance;
	 wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	 wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	 wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	 wndclass.lpszMenuName = NULL;
	 wndclass.lpszClassName = "GameWindow";

	 // Registrando a classe "GameWindow"
	 if (!RegisterClass(&wndclass))
	 {
		 MessageBox(NULL, "Erro na cria��o da janela!", "Game", MB_ICONERROR);
		 return 0;
	 }

	 int windowStyle = WS_OVERLAPPED | WS_SYSMENU;

	 // tela cheia ou janela
	 if (fullScreen)
	 {
		 windowWidth = GetSystemMetrics(SM_CXSCREEN);
		 windowHeight = GetSystemMetrics(SM_CYSCREEN);
		 windowStyle = WS_POPUP;
	 }

	 // criando uma janela baseada na classe "GameWindow"
	 // � necess�rio usar CreateWindowEx para usar AdjustWindowRectEx
	 hwnd = CreateWindowEx(
		 NULL,							// estilos extras
		 "GameWindow",					// nome da "window class"
		 "Mouse Draw",					// t�tulo da janela
		 windowStyle,					// estilo da janela
		 CW_USEDEFAULT,					// posi��o x inicial
		 CW_USEDEFAULT,					// posi��o y inicial
		 windowWidth,					// largura da janela
		 windowHeight,					// altura da janela
		 NULL,							// identificador do objeto pai
		 NULL,							// identificador do menu
		 hInstance,						// identificador da aplica��o
		 NULL);							// par�metros de cria��o

	 if (!fullScreen)
	 {
		 // ret�ngulo com o tamanho da �rea cliente desejada
		 RECT winRect = { 0, 0, windowWidth, windowHeight };

		 // ajuste do tamanho da janela
		 AdjustWindowRectEx(&winRect,
			 GetWindowStyle(hwnd),
			 GetMenu(hwnd) != NULL,
			 GetWindowExStyle(hwnd));

		 // atualiza posi��o da janela
		 int windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((winRect.right - winRect.left) / 2);
		 int windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((winRect.bottom - winRect.top) / 2);

		 // redimensiona janela com uma chamada a MoveWindow
		 MoveWindow(
			 hwnd,							// identificador da janela
			 windowPosX,					// posi��o x
			 windowPosY,					// posi��o y
			 winRect.right - winRect.left,	// largura
			 winRect.bottom - winRect.top,	// altura
			 TRUE);							// repintar
	 }

	 // mostra e atualiza a janela
	 ShowWindow(hwnd, nCmdShow);
	 UpdateWindow(hwnd);
     
	 // Tratamento de mensagens destinadas a janela da aplica��o
     while (GetMessage(&msg, NULL, 0, 0))
     {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
     }

	 // fim do programa
     return msg.wParam;
}

//-------------------------------------------------------------------------------

// procedimento da janela
LRESULT CALLBACK WinProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC hdc;  // representa o dispositivo gr�fico
     
     switch (message)
     {
	 case WM_MOUSEMOVE:                      // mouse - movimento
		 mouseX = LOWORD(lParam);
		 mouseY = HIWORD(lParam);
		 return 0;
	 case WM_LBUTTONDOWN:                    // mouse - bot�o esquerdo pressionado
		 mouseLB = true;
		 InvalidateRect(hwnd, NULL, TRUE);
		 return 0;
	 case WM_LBUTTONUP:                      // mouse - bot�o esquerdo liberado
		 mouseLB = false;
		 return 0;
	 case WM_MBUTTONDOWN:                    // mouse - bot�o do meio pressionado
		 mouseMB = true;
		 InvalidateRect(hwnd, NULL, TRUE);
		 return 0;
	 case WM_MBUTTONUP:                      // mouse - bot�o do meio liberado
		 mouseMB = false;
		 return 0;
	 case WM_RBUTTONDOWN:                    // mouse - bot�o direito pressionado
		 mouseRB = true;
		 InvalidateRect(hwnd, NULL, TRUE);
		 return 0;
	 case WM_RBUTTONUP:                      // mouse - bot�o direito liberado
		 mouseRB = false;
		 return 0;

     // pinta a janela
     case WM_PAINT:
		 hdc = GetDC(hwnd);
		 SetPixel(hdc, mouseX, mouseY, RGB(0,0,0));
		 SetPixel(hdc, mouseX+1, mouseY+1, RGB(0, 0, 0));
		 SetPixel(hdc, mouseX+1, mouseY-1, RGB(0, 0, 0));
		 SetPixel(hdc, mouseX-1, mouseY+1, RGB(0, 0, 0));
		 SetPixel(hdc, mouseX-1, mouseY-1, RGB(0, 0, 0));
		 ReleaseDC(hwnd, hdc);		 
         return 0;

	 // sai do programa   
     case WM_DESTROY:
		 PostQuitMessage(0);
         return 0;
     }
     return DefWindowProc(hwnd, message, wParam, lParam);
}

//-------------------------------------------------------------------------------