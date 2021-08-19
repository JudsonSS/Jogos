/**********************************************************************************
// Galaga (Código Fonte)
// 
// Criação:     23 Set 2011
// Atualização: 18 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Usa a classe Scene para gerenciar muitos objetos na tela
//
**********************************************************************************/

#include "Galaga.h"
#include "Engine.h"
#include "Player.h"
#include "Missile.h"
#include "Alien.h"
#include "Resources.h"

// ------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Scene * Galaga::scene = nullptr; 

// ------------------------------------------------------------------------------

void Galaga::Init()
{
    // ------------------------------
    // cria cena do jogo
    scene = new Scene();

    // ------------------------------
    // cria sprite do fundo e título

    title = new Sprite("Resources/Galaga.png");
    backg = new Sprite("Resources/space.png");

    // ------------------------------
    // cria jogador
    
    scene->Add(new Player());

    // ------------------------------
    // cria alienígenas

    float offset = 80;
    float posY   = 260;

    Alien * alien;
    alien = new Alien("Resources/Alien1.png");
    alien->MoveTo(0, posY);
    scene->Add(alien);

    alien = new Alien("Resources/Alien2.png");
    alien->MoveTo(offset, posY + 30);
    scene->Add(alien);

    alien = new Alien("Resources/Alien3.png");
    alien->MoveTo(2 * offset, posY);
    scene->Add(alien);

    alien = new Alien("Resources/Alien4.png");
    alien->MoveTo(3 * offset, posY + 30);
    scene->Add(alien);

    alien = new Alien("Resources/Alien1.png");
    alien->MoveTo(4 * offset, posY);
    scene->Add(alien);

    alien = new Alien("Resources/Alien2.png");
    alien->MoveTo(5 * offset, posY + 30);
    scene->Add(alien);

    alien = new Alien("Resources/Alien3.png");
    alien->MoveTo(6 * offset, posY);
    scene->Add(alien);

    alien = new Alien("Resources/Alien4.png");
    alien->MoveTo(7 * offset, posY + 30);
    scene->Add(alien);

    // ------------------------------

    posY = 360;

    alien = new Alien("Resources/Alien4.png");
    alien->MoveTo(0, posY);
    scene->Add(alien);

    alien = new Alien("Resources/Alien3.png");
    alien->MoveTo(offset, posY + 30);
    scene->Add(alien);

    alien = new Alien("Resources/Alien2.png");
    alien->MoveTo(2 * offset, posY);
    scene->Add(alien);

    alien = new Alien("Resources/Alien1.png");
    alien->MoveTo(3 * offset, posY + 30);
    scene->Add(alien);

    alien = new Alien("Resources/Alien4.png");
    alien->MoveTo(4 * offset, posY);
    scene->Add(alien);

    alien = new Alien("Resources/Alien3.png");
    alien->MoveTo(5 * offset, posY + 30);
    scene->Add(alien);

    alien = new Alien("Resources/Alien2.png");
    alien->MoveTo(6 * offset, posY);
    scene->Add(alien);

    alien = new Alien("Resources/Alien1.png");
    alien->MoveTo(7 * offset, posY + 30);
    scene->Add(alien);
}

// ------------------------------------------------------------------------------

void Galaga::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza objetos da cena
    scene->Update();
} 

// ------------------------------------------------------------------------------

void Galaga::Draw()
{
    // desenha pano de fundo
    backg->Draw(0, 0, Layer::BACK);

    // desenha título do jogo
    title->Draw(window->CenterX() - title->Width()/2.0f, 30.0f, Layer::FRONT);

    // desenha cena
    scene->Draw();
} 

// ------------------------------------------------------------------------------

void Galaga::Finalize()
{
    // apaga sprites
    delete backg;
    delete title;

    // apaga cena do jogo
    delete scene;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura e inicia o jogo
    engine->window->Mode(WINDOWED);
    engine->window->Size(640, 640);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Galaga");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Galaga());

    // destrói o motor e o jogo
    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

