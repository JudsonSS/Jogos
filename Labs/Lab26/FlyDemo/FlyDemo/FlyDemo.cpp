/**********************************************************************************
// FlyDemo (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Demonstração da inteligência artificial de uma mosca
//
**********************************************************************************/

#include "Engine.h"
#include "FlyDemo.h"
#include "Mouse.h"
#include "TrashCan.h"

// ------------------------------------------------------------------------------

Scene * FlyDemo::scene = nullptr;

// ------------------------------------------------------------------------------

void FlyDemo::Init() 
{
    // carrega sprite do pano de fundo
    backg = new Sprite("Resources/Flyer.png");
    
    // cria cena
    scene = new Scene();

    // adiciona objetos na cena
    scene->Add(new Mouse(), MOVING);
    scene->Add(new TrashCan(), STATIC);
}

// ------------------------------------------------------------------------------

void FlyDemo::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza a cena do jogo
    scene->Update();
    scene->CollisionDetection();

    // visualiza a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;
} 

// ------------------------------------------------------------------------------

void FlyDemo::Draw()
{
    //desenha pano de fundo
    backg->Draw(window->CenterX(), window->CenterY());        

    // desenha cena
    scene->Draw();

    // desenha bouding box
    if (viewBBox)
        scene->DrawBBox();
} 

// ------------------------------------------------------------------------------

void FlyDemo::Finalize()
{
    delete backg;
    delete scene;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor do jogo
    Engine * engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Fly Demo");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // cria e inicia o jogo
    int status = engine->Start(new FlyDemo());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

