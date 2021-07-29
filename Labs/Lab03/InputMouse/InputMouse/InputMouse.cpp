/**********************************************************************************
// InputMouse
// 
// Criação:     13 Abr 2014
// Atualização: 25 Jul 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Demonstra como usar a Window Procedure para capturar o  
//              movimento do mouse e o pressionamento de seus botões.
//
**********************************************************************************/

// inclui tipos básicos e funções da API Win32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>                    // inclui funções do windows
#include <windowsx.h>                   // inclui funções extras do windows
#include "Resources.h"                  // definições dos recursos utilizados
#include <sstream>                      // biblioteca para streamming de strings

using std::stringstream;

//--------------------------------------------------------------------------------
// constantes e variáveis globais
int windowWidth = 800;                  // largura da janela
int windowHeight = 600;                 // altura da janela
bool fullScreen = false;                // tela cheia ou modo janela

const unsigned MaxInputLength = 64;     // tamanho da string
char msg[MaxInputLength] = { 0 };       // mensagem do sistema

int mouseX = 0, mouseY = 0;             // posição do mouse
bool mouseLB = false;                   // botão esquerdo do mouse pressionado
bool mouseMB = false;                   // botão do meio do mouse pressionado
bool mouseRB = false;                   // botão direito do mouse pressionado
short mouseWheel = 0;					// valor da roda do mouse
stringstream text;                      // texto a ser exibido na tela

//--------------------------------------------------------------------------------

// protótipo do procedimento da janela
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
         MessageBox(NULL, "Erro na criação da janela!", "Game", MB_ICONERROR);
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
     // é necessário usar CreateWindowEx para usar AdjustWindowRectEx
     hwnd = CreateWindowEx(
         NULL,                          // estilos extras
         "GameWindow",                  // nome da "window class"
         "Mouse Input",                 // título da janela
         windowStyle,                   // estilo da janela
         CW_USEDEFAULT,                 // posição x inicial
         CW_USEDEFAULT,                 // posição y inicial
         windowWidth,                   // largura da janela
         windowHeight,                  // altura da janela
         NULL,                          // identificador do objeto pai
         NULL,                          // identificador do menu
         hInstance,                     // identificador da aplicação
         NULL);                         // parâmetros de criação

     if (!fullScreen)
     {
         // retângulo com o tamanho da área cliente desejada
         RECT winRect = { 0, 0, windowWidth, windowHeight };

         // ajuste do tamanho da janela
         AdjustWindowRectEx(&winRect,
             GetWindowStyle(hwnd),
             GetMenu(hwnd) != NULL,
             GetWindowExStyle(hwnd));

         // atualiza posição da janela
         int windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - (winRect.right - winRect.left) / 2;
         int windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - (winRect.bottom - winRect.top) / 2;

         // redimensiona janela com uma chamada a MoveWindow
         MoveWindow(
             hwnd,                          // identificador da janela
             windowPosX,                    // posição x
             windowPosY,                    // posição y
             winRect.right - winRect.left,  // largura
             winRect.bottom - winRect.top,  // altura
             TRUE);                         // repintar
     }

     // mostra e atualiza a janela
     ShowWindow(hwnd, nCmdShow);
     UpdateWindow(hwnd);
     
     // Tratamento de mensagens destinadas a janela da aplicação
     while (GetMessage(&msg, NULL, 0, 0))
     {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
     }

     // fim do programa
     return int(msg.wParam);
}

//-------------------------------------------------------------------------------

// procedimento da janela
LRESULT CALLBACK WinProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc;      // representa o dispositivo gráfico
     PAINTSTRUCT ps;       // guarda região invalidada da janela
     RECT        rect;     // região retângular
     
     switch (message)
     {
     // tratamento do mouse
     case WM_MOUSEMOVE:
         mouseX = LOWORD(lParam);
         mouseY = HIWORD(lParam);
         return 0;
     case WM_MOUSEWHEEL:
         mouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
         InvalidateRect(hwnd, NULL, TRUE);
         return 0;
     case WM_LBUTTONDOWN:
         mouseLB = true;
         InvalidateRect(hwnd, NULL, TRUE);
         return 0;
     case WM_LBUTTONUP:
         mouseLB = false;
         return 0;
     case WM_MBUTTONDOWN:
         mouseMB = true;
         InvalidateRect(hwnd, NULL, TRUE);
         return 0;
     case WM_MBUTTONUP:
         mouseMB = false;
         return 0;
     case WM_RBUTTONDOWN:
         mouseRB = true;
         InvalidateRect(hwnd, NULL, TRUE);
         return 0;
     case WM_RBUTTONUP:
         mouseRB = false;
         return 0;

     // pintura da janela
     case WM_PAINT:
         hdc = BeginPaint(hwnd, &ps);
         GetClientRect(hwnd, &rect);
         
         // posição do mouse
         text.str("");
         text << mouseX << " x " << mouseY;
         DrawText(hdc, text.str().c_str(), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
         rect.bottom -= 100;
         DrawText(hdc, "Posição do Click", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

         // botão do mouse
         rect.top += 150;
         if (mouseLB)
            DrawText(hdc, "LEFT", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
         if (mouseRB)
             DrawText(hdc, "RIGHT", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
         if (mouseMB)
             DrawText(hdc, "MIDDLE", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

         // rotação da roda do mouse 
         rect.top += 50;
         if (mouseWheel > 0)
             DrawText(hdc, "Rolagem para frente", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
         if (mouseWheel < 0)
             DrawText(hdc, "Rolagem para trás", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

         EndPaint(hwnd, &ps);
         return 0;

     // sai do programa   
     case WM_DESTROY:
         PostQuitMessage(0);
         return 0;
     }
     return DefWindowProc(hwnd, message, wParam, lParam);
}

//-------------------------------------------------------------------------------