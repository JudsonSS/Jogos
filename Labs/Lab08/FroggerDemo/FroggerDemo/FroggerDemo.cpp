/**********************************************************************************
// FroggerDemo
//
// Criação:     21 Set 2011
// Atualização: 14 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Usa listas de objetos para gerenciar muitos Sprites na tela.
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Resources.h"
#include "Frogger.h"
#include "Obstacle.h"
#include <list>
using std::list;

// ------------------------------------------------------------------------------

class FroggerDemo : public Game
{
private:
    Image * woodSmall   = nullptr;                // pequeno tronco de madeira
    Image * woodBig     = nullptr;                // grande tronco de madeira
    Image * turtleSmall = nullptr;                // pequena fila de tartarugas
    Image * turtleBig   = nullptr;                // grande fila de tartarugas
    Image * truck       = nullptr;                // caminhão tanque
    Image * car1        = nullptr;                // carro de passeio azul
    Image * car2        = nullptr;                // carro de passeio branco
    Image * car3        = nullptr;                // carro de passeio amarelo
    Image * car4        = nullptr;                // carro de passeio vermelho

    Sprite * background = nullptr;                // imagem de fundo
    Frogger * frogger   = nullptr;                // sapo
    Obstacle * obj      = nullptr;                // um obstáculo do jogo

    list<Obstacle*> objects;                      // lista de obstáculos em movimento

public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

// ------------------------------------------------------------------------------

void FroggerDemo::Init()
{
    // carrega imagens do jogo
    woodSmall   = new Image("Resources/woodSmall.png");
    woodBig     = new Image("Resources/woodBig.png");
    turtleSmall = new Image("Resources/turtlesSmall.png");
    turtleBig   = new Image("Resources/turtlesBig.png");
    truck       = new Image("Resources/truck.png");
    car1        = new Image("Resources/car1.png");
    car2        = new Image("Resources/car2.png");
    car3        = new Image("Resources/car3.png");
    car4        = new Image("Resources/car4.png");

    // inicializa sprites do jogo
    background = new Sprite("Resources/Track.jpg");

    frogger = new Frogger();

    // ---------------------------
    // obstáculos da água

    obj = new Obstacle(woodSmall, 80);
    obj->MoveTo(150, 109);
    objects.push_back(obj);

    obj = new Obstacle(woodSmall, 80);
    obj->MoveTo(550, 109);
    objects.push_back(obj);

    obj = new Obstacle(turtleSmall, 70);
    obj->MoveTo(480, 142);
    objects.push_back(obj);

    obj = new Obstacle(turtleSmall, 70);
    obj->MoveTo(680, 142);
    objects.push_back(obj);

    obj = new Obstacle(woodBig, 50);
    obj->MoveTo(200, 190);
    objects.push_back(obj);

    obj = new Obstacle(woodBig, 50);
    obj->MoveTo(700, 190);
    objects.push_back(obj);

    obj = new Obstacle(woodSmall, 60);
    obj->MoveTo(350, 229);
    objects.push_back(obj);

    obj = new Obstacle(turtleBig, 40);
    obj->MoveTo(150, 262);
    objects.push_back(obj);

    obj = new Obstacle(turtleBig, 40);
    obj->MoveTo(450, 262);
    objects.push_back(obj);

    obj = new Obstacle(turtleBig, 40);
    obj->MoveTo(750, 262);
    objects.push_back(obj);

    // ---------------------------
    // obstáculos da pista

    obj = new Obstacle(truck, 50);
    obj->MoveTo(300, 344);
    objects.push_back(obj);

    obj = new Obstacle(truck, 50);
    obj->MoveTo(700, 344);
    objects.push_back(obj);

    obj = new Obstacle(car1, 90);
    obj->MoveTo(350, 384);
    objects.push_back(obj);

    obj = new Obstacle(car4, 90);
    obj->MoveTo(600, 387);
    objects.push_back(obj);

    obj = new Obstacle(car2, 110);
    obj->MoveTo(500, 427);
    objects.push_back(obj);

    obj = new Obstacle(car3, 100);
    obj->MoveTo(750, 467);
    objects.push_back(obj);

    obj = new Obstacle(car4, 80);
    obj->MoveTo(450, 507);
    objects.push_back(obj);
}

// ------------------------------------------------------------------------------

void FroggerDemo::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza posição do sapo
    frogger->Update();

    // move objetos
    for (auto obj : objects)
        obj->Update();
} 

// ------------------------------------------------------------------------------

void FroggerDemo::Draw()
{
    // desenha pano de fundo
    background->Draw(0.0f, 0.0f, Layer::BACK);

    // desenha sapo
    frogger->Draw();

    // desenha obstáculos
    for (auto obj : objects)
        obj->Draw();
}

// ------------------------------------------------------------------------------

void FroggerDemo::Finalize()
{
    // remove objetos da memória
    delete background;
    delete frogger;

    // remove obstáculos
    for (auto obj : objects)
        delete obj;

    // descarrega imagens da memória
    delete woodSmall;
    delete woodBig;
    delete turtleSmall;
    delete turtleBig;
    delete truck;
    delete car1;
    delete car2;
    delete car3;
    delete car4;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Frogger");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    
    // configura dispositivo gráfico
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new FroggerDemo());

    // destrói o motor e o jogo
    delete engine;
    return status;
}

// ----------------------------------------------------------------------------
