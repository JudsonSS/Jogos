/**********************************************************************************
// Platformer (Código Fonte)
//
// Criação:     05 Out 2011
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de jogo estilo platforma
//
**********************************************************************************/

#include "Engine.h"
#include "Platformer.h"
#include "Resources.h"

// -----------------------------------------------------------------------------

Scene * Platformer::scene = nullptr;

// -----------------------------------------------------------------------------

void Platformer::Init()
{
    // cria cena do jogo
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background();
    scene->Add(backg, STATIC);

    // cria jogador
    player = new Player();
    scene->Add(player, MOVING);

    // cria plataformas
    const int MaxPlat = 12;
    Platform * plat[MaxPlat];
    plat[0] = new Platform(700.0f, 100.0f, LARGE);
    plat[1] = new Platform(1500.0f, 200.0f, LARGE);
    plat[2] = new Platform(2000.0f, 50.0f, LARGE);
    plat[3] = new Platform(2500.0f, 200.0f, LARGE);
    plat[4] = new Platform(2950.0f, 50.0f, SMALL);
    plat[5] = new Platform(3200.0f, 250.0f, MEDIUM);
    plat[6] = new Platform(3500.0f, 40.0f, SMALL);
    plat[7] = new Platform(3700.0f, 260.0f, SMALL);
    plat[8] = new Platform(3900.0f, 80.0f, MEDIUM);
    plat[9] = new Platform(4300.0f, 260.0f, LARGE);
    plat[10] = new Platform(4900.0f, 40.0f, MEDIUM);
    plat[11] = new Platform(5500.0f, 260.0f, LARGE);

    for (int i = 0; i < MaxPlat; ++i)
        scene->Add(plat[i], STATIC);
}

// ------------------------------------------------------------------------------

void Platformer::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // ----------------------------------
    // atualiza a posição dos objetos
    // ----------------------------------

    scene->Update();
    scene->CollisionDetection();

    // -------------------------------------------
    // reinicia jogo se o personagem sair da tela
    // -------------------------------------------
    if (player->Y() > window->Height() || player->Y() < 0)
    {
        Finalize();
        Init();
    }
} 

// ------------------------------------------------------------------------------

void Platformer::Draw()
{
    scene->Draw();
} 

// ------------------------------------------------------------------------------

void Platformer::Finalize()
{
    delete scene;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(600, 300);
    engine->window->Color(150, 200, 230);
    engine->window->Title("Platformer");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    int status = engine->Start(new Platformer());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

