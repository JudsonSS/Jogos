/**********************************************************************************
// Engine (Código Fonte)
//
// Criação:     15 Mai 2014
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   A função da Engine é rodar jogos criados a partir da classe
//              abstrata Game. Todo jogo deve ser uma classe derivada de Game
//              e portanto deve implementar as funções membro Init, Update, Draw
//              e Finalize, que serão chamadas pelo motor em um laço de tempo real.
//              Para usar a classe Engine, o programador deve criar uma instância
//              e chamar o método Start(), passando um objeto derivado de Game.
//
**********************************************************************************/

#include "Engine.h"
#include <windows.h>
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

Game     * Engine::game      = nullptr;     // jogo em execução
Window   * Engine::window    = nullptr;     // janela do jogo
Graphics * Engine::graphics  = nullptr;     // dispositivo gráfico
Renderer * Engine::renderer  = nullptr;     // renderizador de sprites 
float      Engine::frameTime = 0.0f;        // tempo do quadro atual
bool       Engine::paused    = false;       // estado do game loop
Timer      Engine::timer;                   // medidor de tempo

// -------------------------------------------------------------------------------

Engine::Engine()
{
    window     = new Window();
    graphics   = new Graphics();
    renderer   = new Renderer();
}

// -------------------------------------------------------------------------------

Engine::~Engine()
{
    delete game;
    delete renderer;
    delete graphics;
    delete window;
}

// -----------------------------------------------------------------------------

int Engine::Start(Game* level)
{
    game = level;

    // cria janela do jogo
    window->Create();

    // inicializa dispositivo gráfico
    graphics->Initialize(window);

    // inicializa renderizador de sprites
    renderer->Initialize(window, graphics);

    // ajusta a resolução do Sleep para 1 milisegundo
    // requer uso da biblioteca winmm.lib
    timeBeginPeriod(1);

    int exitCode = Loop();

    // volta a resolução do Sleep ao valor original
    timeEndPeriod(1);

    return exitCode;
}

// -----------------------------------------------------------------------------

void Engine::Pause()
{
    paused = true;
    timer.Stop();
}

// -----------------------------------------------------------------------------

void Engine::Resume()
{
    paused = false;
    timer.Start();
}

// -------------------------------------------------------------------------------

int Engine::Loop()
{
    // inicia contagem de tempo
    timer.Start();

    // inicialização do jogo
    game->Init();

    // mensagens do Windows
    MSG  msg = { 0 };

    // laço principal do jogo
    do
    {
        // testa se tem mensagem do windows para tratar
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // -----------------------------------------------
            // Pausa/Resume Jogo
            // -----------------------------------------------

            if (window->KeyPress(VK_PAUSE))
            {
                paused = !paused;

                if (paused)
                    timer.Stop();
                else
                    timer.Start();
            }

            // -----------------------------------------------

            if (!paused)
            {
                // calcula o tempo do quadro
                frameTime = FrameTime();

                // atualização do jogo 
                game->Update();

                // limpa a tela para o próximo quadro
                graphics->Clear();

                // desenha o jogo
                game->Draw();

                // renderiza sprites
                renderer->Render();

                // apresenta o jogo na tela (troca backbuffer/frontbuffer)
                graphics->Present();
            }
            else
            {
                // tela de pausa
                game->OnPause();
            }
        }

    } while (msg.message != WM_QUIT);

    // finalização do jogo
    game->Finalize();

    // encerra aplicação
    return int(msg.wParam);
}

// -----------------------------------------------------------------------------

float Engine::FrameTime()
{
#ifdef _DEBUG
    static float totalTime = 0.0f;    // tempo total transcorrido 
    static uint  frameCount = 0;      // contador de frames transcorridos
#endif
    
    // tempo do frame atual em segundos
    frameTime = timer.Reset();
    
#ifdef _DEBUG
    // tempo acumulado dos frames
    totalTime += frameTime;

    // incrementa contador de frames
    frameCount++;

    // a cada 1000ms (1 segundo) atualiza indicador de FPS na janela
    if (totalTime >= 1.0f)
    {
        stringstream text;            // fluxo de texto para mensagens
        text << std::fixed;           // sempre mostra a parte fracionária
        text.precision(3);            // três casas depois da vírgula

        text << window->Title().c_str() << "    "
            << "FPS: " << frameCount << "    "
            << "Frame Time: " << frameTime * 1000 << " (ms)";

        SetWindowText(window->Id(), text.str().c_str());

        frameCount = 0;
        totalTime -= 1.0f;
    }
#endif

    return frameTime;
}

// -----------------------------------------------------------------------------
