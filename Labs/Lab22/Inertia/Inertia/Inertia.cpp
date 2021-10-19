/**********************************************************************************
// Inertia (Código Fonte)
// 
// Criação:     14 Mar 2013
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Movimentação por aplicação de um vetor Força
//
**********************************************************************************/

#include "Engine.h"
#include "Inertia.h"

// ------------------------------------------------------------------------------

Scene * Inertia::scene = nullptr;            // cena do jogo
Audio * Inertia::audio = nullptr;            // sistema de áudio
TileSet * Inertia::exploSet = nullptr;       // tileset da explosão

// ------------------------------------------------------------------------------

void Inertia::Init() 
{
    // cria sistema de áudio
    audio = new Audio();

    // carrega arquivos de som
    audio->Add(FIRE, "Resources/Pulse.wav", 3);
    audio->Add(EXPLOSION, "Resources/Explosion.wav", 5);
    audio->Add(JETUP, "Resources/JetStart.wav");
    audio->Add(LOOPUP, "Resources/JetLoop.wav");
    audio->Add(JETDOWN, "Resources/JetStart.wav");
    audio->Add(LOOPDOWN, "Resources/JetLoop.wav");

    // configura volumes 
    audio->Volume(FIRE, 0.7f);
    audio->Volume(EXPLOSION, 0.2f);
    audio->Volume(JETDOWN, 0.9f);
    audio->Volume(LOOPDOWN, 0.9f);

    // configura frequências
    audio->Frequency(JETDOWN, 0.5f);
    audio->Frequency(LOOPDOWN, 0.5f);

    // cria fonte para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Tahoma14b.png");
    bold->Spacing("Resources/Tahoma14b.dat");

    // carrega sprites e tileset
    backg = new Sprite("Resources/SpaceArt.jpg");
    keyMap = new Sprite("Resources/KeyMap.png");
    exploSet = new TileSet("Resources/Explosion.png", 64, 64, 5, 10);

    // cria cena do jogo
    scene = new Scene();
    ship = new Ship();
    scene->Add(ship, STATIC);
}

// ------------------------------------------------------------------------------

void Inertia::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza cena do jogo
    scene->Update();
} 

// ------------------------------------------------------------------------------

void Inertia::Draw()
{
    // desenha pano de fundo
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    // desenha elementos sobrepostos
    keyMap->Draw(window->CenterX(), window->Height() - 20.0f, Layer::FRONT);

    // desenha cena do jogo
    scene->Draw();

    // desenha texto
    Color gray { 0.70f, 0.70f, 0.70f, 1.0f };
    Color blue { 0.60f, 0.60f, 0.65f, 1.0f };
    bold->Draw(window->CenterX() - 5.0f, window->Height() - 14.0f, "Inércia", gray);
    font->Draw(window->CenterX() - 218.0f, window->Height() - 4.0f, "Disparo", blue);
    font->Draw(window->CenterX() - 124.0f, window->Height() - 4.0f, "Espaço", blue);
    font->Draw(window->CenterX() + 124.0f, window->Height() - 4.0f, "Setas", blue);
    font->Draw(window->CenterX() + 196.0f, window->Height() - 4.0f, "Movimentação", blue);
}

// ------------------------------------------------------------------------------

void Inertia::Finalize()
{
    delete exploSet;
    delete backg;
    delete keyMap;
    delete scene;
    delete audio;
    delete font;
    delete bold;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura motor
    //engine->window->Mode(WINDOWED);
    //engine->window->Size(1200, 640);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Inertia");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Inertia());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

