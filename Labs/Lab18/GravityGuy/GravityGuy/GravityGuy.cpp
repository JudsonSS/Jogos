/**********************************************************************************
// GravityGuy (Código Fonte)
// 
// Criação:     05 Out 2011
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Jogo estilo plataforma usando a engine do curso
//
**********************************************************************************/

#include "Engine.h"
#include "GravityGuy.h"
#include "Home.h"
#include "GameOver.h"

// ------------------------------------------------------------------------------

// inicializa membros estáticos da classe
Game*   GravityGuy::level = nullptr;
Player* GravityGuy::player = nullptr;
Audio*  GravityGuy::audio = nullptr;
bool    GravityGuy::viewBBox = false;

// ------------------------------------------------------------------------------

void GravityGuy::Init() 
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(MENU, "Resources/Menu.wav");
    audio->Add(MUSIC, "Resources/Music.wav");
    audio->Add(TRANSITION, "Resources/Transition.wav");

    // bounding box não visível
    viewBBox = false;

    // cria jogador
    player = new Player();

    // inicializa nível de abertura do jogo
    level = new Home();
    level->Init();
}

// ------------------------------------------------------------------------------

void GravityGuy::Update()
{
    // habilita/desabilita visualização da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;    

    // atualiza nível
    level->Update();
} 

// ------------------------------------------------------------------------------

void GravityGuy::Draw()
{
    // desenha nível
    level->Draw();
} 

// ------------------------------------------------------------------------------

void GravityGuy::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura o motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(600, 300);
    engine->window->Color(30, 50, 80);
    engine->window->Title("Gravity Guy");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new GravityGuy());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

