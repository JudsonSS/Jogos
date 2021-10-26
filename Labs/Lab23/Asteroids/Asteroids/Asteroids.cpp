/**********************************************************************************
// Asteroids (Código Fonte)
// 
// Criação:     14 Mar 2013
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Colisão com Polígonos
//
**********************************************************************************/

#include "Engine.h"
#include "Asteroids.h"
#include "Rock.h"

// ------------------------------------------------------------------------------

Scene * Asteroids::scene = nullptr;         // cena do jogo
Audio * Asteroids::audio = nullptr;         // sistema de áudio
TileSet * Asteroids::exploSet = nullptr;    // tileset da explosão
TileSet * Asteroids::debriSet = nullptr;    // tileset dos pedaços de rocha

// ------------------------------------------------------------------------------

void Asteroids::Init() 
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

    // cria cena do jogo
    scene = new Scene();

    // cria e adiciona nave na cena
    ship = new Ship();
    scene->Add(ship, MOVING);

    // cria e adiciona asteroides na cena
    for (int i = 0; i < 25; ++i)
        scene->Add(new Rock(), MOVING);
    
    // carrega pano de fundo e elementos sobrepostos
    backg = new Sprite("Resources/Space.jpg");
    keyMap = new Sprite("Resources/KeyMap.png");

    // carrega folhas de sprites da explosão
    exploSet = new TileSet("Resources/Explosion.png", 64, 64, 5, 10);
    debriSet = new TileSet("Resources/Debris.png", 125, 75, 8, 8);
}

// ------------------------------------------------------------------------------

void Asteroids::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // habilita/desabilita bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // atualiza cena do jogo
    scene->Update();
    scene->CollisionDetection();
} 

// ------------------------------------------------------------------------------

void Asteroids::Draw()
{
    // desenha pano de fundo
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    // desenha elementos sobrepostos
    keyMap->Draw(window->CenterX(), window->Height() - 20.0f, Layer::FRONT);

    // desenha cena do jogo
    scene->Draw();

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();

    // desenha texto
    Color gray { 0.70f, 0.70f, 0.70f, 1.0f };
    Color blue { 0.60f, 0.60f, 0.65f, 1.0f };
    bold->Draw(window->CenterX() - 12.0f, window->Height() - 14.0f, "Asteroids", gray);
    font->Draw(window->CenterX() - 218.0f, window->Height() - 4.0f, "Disparo", blue);
    font->Draw(window->CenterX() - 124.0f, window->Height() - 4.0f, "Espaço", blue);
    font->Draw(window->CenterX() + 124.0f, window->Height() - 4.0f, "Setas", blue);
    font->Draw(window->CenterX() + 196.0f, window->Height() - 4.0f, "Movimentação", blue);

    // mostra quantidade de asteroids ativos
    //text.str("");
    //text << Rock::count;
    //font->Draw(30.0f, 30.0f, text.str(), gray);
}

// ------------------------------------------------------------------------------

void Asteroids::Finalize()
{
    delete debriSet;
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
    engine->window->Title("Asteroids");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Asteroids());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

