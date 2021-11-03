/**********************************************************************************
// Window (Código Fonte)
// 
// Criação:     19 Mai 2007
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   A classe abstrai todos os detalhes de configuração de
//              uma janela para um jogo. 
//
**********************************************************************************/

#include "Window.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe
bool Window::windowKeys[256] = { 0 };                       // estado do teclado/mouse
bool Window::windowCtrl[256] = { 0 };                       // controle de teclado/mouse
int  Window::windowMouseX = 0;                              // posição do mouse no eixo x
int  Window::windowMouseY = 0;                              // posição do mouse no eixo y
int  Window::windowMouseWheel = 0;                          // giro da roda do mouse

// -------------------------------------------------------------------------------
// Construtor

Window::Window()
{
    hInstance       = GetModuleHandle(NULL);                // identificador da aplicação
    windowHandle    = 0;                                    // identificador da janela do jogo
    windowWidth     = GetSystemMetrics(SM_CXSCREEN);        // a janela ocupa toda a tela (tela cheia)
    windowHeight    = GetSystemMetrics(SM_CYSCREEN);        // a janela ocupa toda a tela (tela cheia)
    windowIcon      = LoadIcon(NULL, IDI_APPLICATION);      // ícone padrão de uma aplicação
    windowCursor    = LoadCursor(NULL, IDC_ARROW);          // cursor padrão de uma aplicação
    windowColor     = RGB(0,0,0);                           // cor de fundo padrão é preta
    windowTitle     = string("Windows Game");               // título padrão da janela
    windowStyle     = WS_POPUP | WS_VISIBLE;                // estilo para tela cheia
    windowMode      = FULLSCREEN;                           // modo padrão é tela cheia
    windowPosX      = 0;                                    // posição inicial da janela no eixo x
    windowPosY      = 0;                                    // posição inicial da janela no eixo y
    windowCenterX   = windowWidth/2.0f;                     // centro da janela no eixo x
    windowCenterY   = windowHeight/2.0f;                    // centro da janela no eixo y
}

// -------------------------------------------------------------------------------

void Window::Mode(int mode)
{
    windowMode = mode;

    if (mode == WINDOWED)
    {
        // modo em janela
        windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE; 
    }
    else
    {
        // modo em tela cheia ou sem bordas
        windowStyle = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE; 
    } 
}

// -------------------------------------------------------------------------------

void Window::Size(int width, int height)
{ 
    // window size
    windowWidth = width; 
    windowHeight = height;

    // calcula a posição do centro da janela
    windowCenterX = windowWidth / 2.0f;
    windowCenterY = windowHeight / 2.0f;

    // ajusta a posição da janela para o centro da tela
    windowPosX = GetSystemMetrics(SM_CXSCREEN)/2 - windowWidth/2;
    windowPosY = GetSystemMetrics(SM_CYSCREEN)/2 - windowHeight/2;
}

// -------------------------------------------------------------------------------

bool Window::KeyPress(int vkcode)
{
    if (windowCtrl[vkcode])
    {
        if (KeyDown(vkcode))
        {
            windowCtrl[vkcode] = false;
            return true;
        }
    }
    else if (KeyUp(vkcode))
    {
        windowCtrl[vkcode] = true;
    }

    return false;
}


// -------------------------------------------------------------------------------

bool Window::Create()
{
    WNDCLASSEX wndClass; 
    
    // definindo uma classe de janela chamada "GameWindow"
    wndClass.cbSize         = sizeof(WNDCLASSEX);
    wndClass.style          = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc    = Window::WinProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = windowIcon;
    wndClass.hCursor        = windowCursor; 
    wndClass.hbrBackground  = (HBRUSH) CreateSolidBrush(windowColor);
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = "GameWindow";
    wndClass.hIconSm        = windowIcon;

    // registrando "GameWindow"
    if (!RegisterClassEx(&wndClass))
        return false;

    // criando uma janela baseada na classe "GameWindow" 
    windowHandle = CreateWindowEx(
        NULL,                           // estilos extras
        "GameWindow",                   // nome da "window class"
        windowTitle.c_str(),            // título da janela
        windowStyle,                    // estilo da janela
        windowPosX, windowPosY,         // posição (x,y) inicial
        windowWidth, windowHeight,      // largura e altura da janela
        NULL,                           // identificador da janela pai
        NULL,                           // identificador do menu
        hInstance,                      // identificador da aplicação
        NULL);                          // parâmetros de criação

    // Ao usar o modo em janela é preciso levar em conta que as barras 
    // e bordas ocupam espaço na janela. O código abaixo ajusta o tamanho
    // da janela de forma que a área cliente do jogo fique no tamanho 
    // (windowWidth x windowHeight)

    if (windowMode == WINDOWED)
    {
        // retângulo com o tamanho da área cliente desejada
        RECT winRect = {0, 0, windowWidth, windowHeight};

        // ajusta o tamanho do retângulo
        AdjustWindowRectEx(&winRect,
            GetWindowStyle(windowHandle),
            GetMenu(windowHandle) != NULL,
            GetWindowExStyle(windowHandle));

        // atualiza posição da janela
        windowPosX = GetSystemMetrics(SM_CXSCREEN)/2 - (winRect.right - winRect.left)/2;
        windowPosY = GetSystemMetrics(SM_CYSCREEN)/2 - (winRect.bottom - winRect.top)/2;

        // redimensiona janela com uma chamada a MoveWindow
        MoveWindow(
            windowHandle,                  // identificador da janela
            windowPosX,                    // posição x
            windowPosY,                    // posição y
            winRect.right - winRect.left,  // largura
            winRect.bottom - winRect.top,  // altura
            TRUE);                         // repintar
    }

    // retorna estado da inicialização (bem sucedida ou não)
    return (windowHandle ? true : false);
}

// -------------------------------------------------------------------------------

LRESULT CALLBACK Window::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        // movimento do mouse
    case WM_MOUSEMOVE:
        windowMouseX = GET_X_LPARAM(lParam);
        windowMouseY = GET_Y_LPARAM(lParam);
        return 0;

    case WM_MOUSEWHEEL:
        windowMouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
        return 0;

        // tecla pressionada
    case WM_KEYDOWN:
        windowKeys[wParam] = true;
        return 0;


        // botão esquerdo do mouse pressionado
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        windowKeys[VK_LBUTTON] = true;
        return 0;

        // botão do meio do mouse pressionado
    case WM_MBUTTONDOWN:
    case WM_MBUTTONDBLCLK:
        windowKeys[VK_MBUTTON] = true;
        return 0;

        // botão direito do mouse pressionado
    case WM_RBUTTONDOWN:
    case WM_RBUTTONDBLCLK:
        windowKeys[VK_RBUTTON] = true;
        return 0;

        // tecla liberada
    case WM_KEYUP:
        windowKeys[wParam] = false;
        return 0;

        // botão esquerdo do mouse liberado
    case WM_LBUTTONUP:
        windowKeys[VK_LBUTTON] = false;
        return 0;

        // botão do meio do mouse liberado
    case WM_MBUTTONUP:
        windowKeys[VK_MBUTTON] = false;
        return 0;

        // botão direito do mouse liberado
    case WM_RBUTTONUP:
        windowKeys[VK_RBUTTON] = false;
        return 0;

        // mudança de foco da janela
    case WM_SETFOCUS:
        Engine::Resume();
        return 0;
    case WM_KILLFOCUS:
        Engine::Pause();
        return 0;

        // a janela foi destruida
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// -----------------------------------------------------------------------------
