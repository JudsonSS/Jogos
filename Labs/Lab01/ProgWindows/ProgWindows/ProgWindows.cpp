/**********************************************************************************
// ProgWindows
// 
// Criação:     06 Mai 2011
// Atualização: 14 Jul 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Esqueleto básico de criação de uma janela no Windows 
//              usando a API Win32. Este esqueleto pode ser usado como ponto
//              de partida para criação de qualquer aplicação.
//
**********************************************************************************/

// inclui tipos básicos e funções da API Win32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// protótipo do procedimento da janela
LRESULT CALLBACK WinProc (HWND, UINT, WPARAM, LPARAM);

//--------------------------------------------------------------------------------

// programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
     HWND         hwnd;        // identificador da janela
     MSG          msg;         // mensagem
     WNDCLASS     wndclass;    // classe da janela

     // Definindo uma classe de janela chamada "BasicWindow" 
     wndclass.style         = CS_HREDRAW | CS_VREDRAW;
     wndclass.lpfnWndProc   = WinProc;
     wndclass.cbClsExtra    = 0;
     wndclass.cbWndExtra    = 0;
     wndclass.hInstance     = hInstance;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
     wndclass.lpszMenuName  = NULL;
     wndclass.lpszClassName = "BasicWindow";

     // Registrando a classe "BasicWindow"
     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, "Erro na criação da janela!", "Aplicação", MB_ICONERROR);
          return 0 ;
     }

     // Criando uma janela baseada na classe "BasicWindow" 
     hwnd = CreateWindow ("BasicWindow",                // classe da janela
                          "Aplicação",                  // título da janela
                          WS_OVERLAPPEDWINDOW,          // estilo da janela
                          CW_USEDEFAULT,                // posição x inicial
                          CW_USEDEFAULT,                // posição y inicial
                          CW_USEDEFAULT,                // largura inicial
                          CW_USEDEFAULT,                // altura inicial
                          NULL,                         // identificador da janela pai
                          NULL,                         // identificador do menu
                          hInstance,                    // identificador da aplicação
                          NULL);                        // parâmetros de criação
     
     // Mostra e atualiza a janela
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
     case WM_PAINT:
          hdc = BeginPaint(hwnd, &ps);
          
          GetClientRect(hwnd, &rect);
          DrawText(hdc, "Oi Janela!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

          EndPaint(hwnd, &ps);
          return 0;
          
     case WM_DESTROY:
         PostQuitMessage(0);
         return 0;
     }
     return DefWindowProc(hwnd, message, wParam, lParam);
}

//-------------------------------------------------------------------------------