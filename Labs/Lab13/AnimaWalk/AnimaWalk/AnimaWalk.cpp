/**********************************************************************************
// AnimaWalk (Código Fonte)
// 
// Criação:     18 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Usando a classe Animation para animar um personagem
//
**********************************************************************************/

#include "Engine.h"
#include "AnimaWalk.h"
#include "Resources.h"

// -----------------------------------------------------------------------------

void AnimaWalk::Init()
{
    backg = new Sprite("Resources/Background.jpg");
    lady  = new Lady();
}

// ------------------------------------------------------------------------------

void AnimaWalk::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza objeto
    lady->Update();
} 

// ------------------------------------------------------------------------------

void AnimaWalk::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    lady->Draw();
} 

// ------------------------------------------------------------------------------

void AnimaWalk::Finalize()
{
    delete lady;
    delete backg;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura a engine
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(0, 0, 0);
    engine->window->Title("AnimaWalk");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    int status = engine->Start(new AnimaWalk());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

