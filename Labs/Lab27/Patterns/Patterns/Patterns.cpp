/**********************************************************************************
// Patterns (Código Fonte)
// 
// Criação:     17 Out 2012
// Atualização: 10 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Aplicação de padrões e scripts em jogos
//
**********************************************************************************/

#include "Engine.h"
#include "Patterns.h"
#include "Stage.h"

// ------------------------------------------------------------------------------

Audio * Patterns::audio = nullptr;
Scene * Patterns::scene = nullptr;

// ------------------------------------------------------------------------------

void Patterns::Init()
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(MUSIC, "Resources/Music.wav");
    audio->Add(MISSILE, "Resources/Missile.wav", 3);
    audio->Add(ALIEN1, "Resources/Alien1.wav");
    audio->Add(ALIEN2, "Resources/Alien2.wav");
    audio->Add(ALIEN3, "Resources/Alien3.wav");
    audio->Add(ALIEN4, "Resources/Alien4.wav");
    audio->Volume(MISSILE, 0.6f);
    audio->Volume(ALIEN1, 0.6f);
    audio->Volume(ALIEN2, 0.6f);

    // cria cena do jogo
    scene = new Scene();
    scene->Add(new Backg(), STATIC);
    scene->Add(new Player(), STATIC);
    scene->Add(new Stage(), STATIC);
}

// ------------------------------------------------------------------------------

void Patterns::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza a cena
    scene->Update();
    scene->CollisionDetection();

    // habilita visualização da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;
} 

// ------------------------------------------------------------------------------

void Patterns::Draw()
{
    // desenha a cena
    scene->Draw();

    // desenha a bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
} 

// ------------------------------------------------------------------------------

void Patterns::Finalize()
{
    // libera memória alocada
    delete scene;
    delete audio;
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
    engine->window->Size(720, 576);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Patterns");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);

    // cria e inicia o jogo
    int status = engine->Start(new Patterns());

    // destrói motor
    delete engine;

    // encerra
    return status;
}

// ----------------------------------------------------------------------------
