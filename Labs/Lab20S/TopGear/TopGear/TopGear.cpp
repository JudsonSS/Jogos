/**********************************************************************************
// TopGear (Código Fonte)
//
// Criação:     11 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplificando o uso da escala
//
**********************************************************************************/

#include "Engine.h"
#include "TopGear.h"
#include "Stripes.h"
#include "Player.h"
#include "Cars.h"

// ------------------------------------------------------------------------------
// inicialização de membros estáticos da classe

Audio * TopGear::audio = nullptr;
float   TopGear::speed = 1000.0f;

// ------------------------------------------------------------------------------

void TopGear::Init()
{
    // cria gerenciadores
    scene = new Scene();
    audio = new Audio();

    // carregar músicas e efeitos sonoros
    audio->Add(MUSIC, "Resources/Soundtrack.wav");
    audio->Add(ENGINE, "Resources/CarEngine.wav");
    audio->Add(COLLISION, "Resources/Collision.wav");

    // carrega sprites e imagens
    sky = new Sprite("Resources/Sky.png");
    track = new Sprite("Resources/Track.png");

    // cria e adiciona jogador na cena
    Player * player = new Player();
    scene->Add(player, MOVING);

    // cria e adiciona linhas da pista na cena
    Stripes * stripes = new Stripes();
    scene->Add(stripes, STATIC);

    // cria e adiciona carros adversários na cena
    Cars * cars = new Cars();
    scene->Add(cars, STATIC);

    // inicia música e motor do carro
    audio->Volume(ENGINE, 0.25f);
    audio->Play(MUSIC, true);    
    audio->Play(ENGINE, true);
}

// ------------------------------------------------------------------------------

void TopGear::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza a cena 
    scene->Update();
    scene->CollisionDetection();

    // habilita/desabilita bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;
} 

// ------------------------------------------------------------------------------

void TopGear::Draw()
{
    // desenha o pano de fundo
    track->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    sky->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);
    
    // desenha a cena
    scene->Draw();

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
} 

// ------------------------------------------------------------------------------

void TopGear::Finalize()
{
    delete track;
    delete sky;
    delete scene;
    delete audio;
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
    engine->window->Size(960, 540);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Top Gear");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new TopGear());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

