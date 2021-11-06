/**********************************************************************************
// SoftChase (Código Fonte)
// 
// Criação:     23 Out 2012
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Demonstração da perseguição suavizada
//
**********************************************************************************/

#include "Resources.h"
#include "SoftChase.h"
#include "Engine.h"    
#include "Blue.h"
#include "Wave.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

Audio  * SoftChase::audio = nullptr;
Scene  * SoftChase::scene = nullptr;
Player * SoftChase::player = nullptr;

// ------------------------------------------------------------------------------

void SoftChase::Init()
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(FIRE, "Resources/Fire.wav");
    audio->Add(EXPLODE, "Resources/Explode.wav");
    audio->Add(HITWALL, "Resources/Hitwall.wav");
    audio->Add(THEME, "Resources/Theme.wav");
    audio->Add(SPAWN, "Resources/Blue.wav");
        
    // ajusta volumes
    audio->Volume(FIRE, 0.2f);
    audio->Volume(EXPLODE, 0.3f);
    audio->Volume(SPAWN, 0.5f);
    audio->Volume(THEME, 0.8f);

    // carrega pano de fundo
    backg = new Sprite("Resources/Space.jpg");
    
    // cria gerenciador de cena
    scene = new Scene();    

    // cria objetos
    player = new Player();
    hud = new Hud();

    // adiciona objetos na cena
    scene->Add(player, STATIC);
    scene->Add(new Wave(), STATIC);

    // toca música
    audio->Play(THEME, true);
}

// ------------------------------------------------------------------------------

void SoftChase::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza cena e calcula colisões
    scene->Update();
    scene->CollisionDetection();

    // atualiza mostradores da interface
    hud->Update();

    // ativa ou desativa a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;
} 

// ------------------------------------------------------------------------------

void SoftChase::Draw()
{
    // desenha pano de fundo
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    // desenha heads up display
    hud->Draw();

    // desenha a cena
    scene->Draw();

    // desenha bounding box
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void SoftChase::Finalize()
{
    delete audio;
    delete scene;
    delete backg;
    delete hud;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor do jogo
    Engine * engine = new Engine();

    // configura janela
    //engine->window->Mode(WINDOWED);
    //engine->window->Size(1152, 648);
    engine->window->Mode(BORDERLESS);
    engine->window->Color(0, 0, 0);
    engine->window->Title("SoftChase");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    
    // inicia jogo
    int status = engine->Start(new SoftChase());

    // destrói motor e retorna
    delete engine;
    return status;
}

// ----------------------------------------------------------------------------