/**********************************************************************************
// Balloons (Código Fonte)
// 
// Criação:     28 Out 2011
// Atualização: 22 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de uso do mouse e teclado
//
**********************************************************************************/

#include "Engine.h"
#include "Balloons.h"
#include "Ball.h"
#include "Click.h"

// ------------------------------------------------------------------------------

Scene * Balloons::scene = nullptr;
Audio * Balloons::audio = nullptr;
uint Balloons::popped = 0;
uint Balloons::lost = 0;

// ------------------------------------------------------------------------------

void Balloons::Init() 
{
    // cria gerenciadores
    audio = new Audio();
    scene = new Scene();

    // carrega sons e músicas
    audio->Add(MUSIC, "Resources/Music.wav");
    audio->Add(POP, "Resources/Popping.wav", 3);
    
    // carrega imagens
    ball = new Image("Resources/Balloon.png");
    tilesClick = new TileSet("Resources/Click.png", 64, 64, 3, 3);
    tilesPop = new TileSet("Resources/Popping.png", 128, 128, 4, 4);
    
    // sorteia posição do primeiro balão
    float posX = randWidth(mt);  
    float posY = randHeight(mt);
    float oldX;

    Ball * balloon = nullptr;

    // cria alguns balões em posições aleatórias
    for (int i = 0; i < 5; ++i)   
    {
        Color color{ randColor(mt), randColor(mt), randColor(mt), 1.0f };
        
        balloon = new Ball(ball, tilesPop, color);
        balloon->MoveTo(posX, posY);
        scene->Add(balloon, STATIC);

        oldX = posX;

        while (abs(posX - oldX) < 100)
        {
            posX = randWidth(mt);
            posY = randHeight(mt);
        }
    }

    // carrega sprites 
    backg = new Sprite("Resources/Wallpaper.jpg");
    popBox = new Sprite("Resources/Green.png");
    lostBox = new Sprite("Resources/Red.png");
    infoBar = new Sprite("Resources/InfoBar.png");

    // cria fontes
    sysFont = new Font("Resources/Agency30.png");
    sysFont->Spacing("Resources/Agency30.dat");
    gameFont = new Font("Resources/Agency40.png");
    gameFont->Spacing("Resources/Agency40.dat");

    // inicia música 
    audio->Volume(MUSIC, 0.5f);
    audio->Play(MUSIC, true);
    
    // inicia timer para criação de balões
    timer.Start();
}

// ------------------------------------------------------------------------------

void Balloons::Update()
{
    // fecha janela ao pressionar ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // cria um novo balão a cada 0.5 segundo
    if (timer.Elapsed(0.5f))
    {
        float oldX = posX;

        while (abs(posX - oldX) < 100)
        {
            posX = randWidth(mt);
            posY = randHeight(mt);
        }

        Color color{ randColor(mt), randColor(mt), randColor(mt), 1.0f };

        Ball * balloon = new Ball(ball, tilesPop, color);
        balloon->MoveTo(posX, posY);
        scene->Add(balloon, STATIC);
        timer.Reset();
    }

    // adiciona objetos click
    if (window->KeyPress(VK_LBUTTON) || window->KeyPress(VK_SPACE))
    {
        Click * click = new Click(tilesClick);
        click->MoveTo(window->MouseX(), window->MouseY());
        scene->Add(click, MOVING);
    }

    // habilita/desabilita bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // atualiza cena e detecta colisões
    scene->Update();
    scene->CollisionDetection();
} 

// ------------------------------------------------------------------------------

void Balloons::Draw()
{
    // desenha sprites fixos
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    infoBar->Draw(window->CenterX(), window->Height() - 22.0f, Layer::UPPER);
    popBox->Draw(65, window->Height() - 55.0f, Layer::UPPER);
    lostBox->Draw(window->Width() - 65.0f, window->Height() - 55.0f, Layer::UPPER);

    // desenha cena
    scene->Draw();

    // desenha placar dos balões estourados
    text.str("");
    text << popped;
    int length = int(text.tellp());
    gameFont->Draw(60 - (5.0f * length), window->Height() - 20.0f, text.str());

    // desenha placar dos balões perdidos
    text.str("");
    text << lost;
    length = int(text.tellp());
    gameFont->Draw(window->Width() - 10.0f - (5.0f * length), window->Height() - 20.0f, text.str());

    // desenha instruções do jogo
    text.str("");
    text << "Estoure os balões com o Botão Esquerdo ou Barra de Espaços";
    sysFont->Draw(window->CenterX() - 215.0f, window->Height() - 20.0f, text.str(), Color(0.1f, 0.1f, 0.1f, 1.0f));

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
} 

// ------------------------------------------------------------------------------

void Balloons::Finalize()
{
    // remove sprites
    delete popBox;
    delete lostBox;
    delete infoBar;
    delete backg;

    // remove imagens
    delete tilesPop;
    delete tilesClick;
    delete ball;
    
    // remove fontes 
    delete sysFont;
    delete gameFont;
    
    // remove gerentes
    delete scene;
    delete audio;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Balloons demo;

    Engine * engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1280, 800);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Balloons");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Balloons());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

