/**********************************************************************************
// D3DGame
// 
// Criação:     06 Mar 2012
// Atualização: 08 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Ilustra utilização da classe Graphics construindo uma 
//              janela vazia que está sendo atualizada com o Direct3D.
//
**********************************************************************************/

#include "Resources.h"
#include "Engine.h"
#include "Game.h"

// ------------------------------------------------------------------------------

class D3DGame : public Game
{
private:

public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

// ------------------------------------------------------------------------------

void D3DGame::Init() 
{
}

// ------------------------------------------------------------------------------

void D3DGame::Update()
{
    if (window->KeyDown(VK_ESCAPE))
        window->Close();
} 

// ------------------------------------------------------------------------------

void D3DGame::Draw()
{    
} 

// ------------------------------------------------------------------------------

void D3DGame::Finalize()
{
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor 
    Engine * engine = new Engine();

    // configura a janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(240, 240, 140);
    engine->window->Title("D3D Game");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // cria e inicia o jogo
    int exit_code = engine->Start(new D3DGame());

    // finaliza jogo e motor
    delete engine;
    return exit_code;
}

// ----------------------------------------------------------------------------

