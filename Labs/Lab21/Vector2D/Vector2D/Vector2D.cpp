/**********************************************************************************
// Vector2D (Código Fonte)
//
// Criação:     11 Nov 2011
// Atualização: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de utilização da classe Vector
//
**********************************************************************************/

#include "Engine.h"
#include "Vector2D.h"

// ------------------------------------------------------------------------------

Scene * Vector2D::scene = nullptr;            // gerenciador de cena 
Audio * Vector2D::audio = nullptr;            // sistema de áudio

// ------------------------------------------------------------------------------

void Vector2D::Init()
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(PULSE, "Resources/Pulse.wav");
    audio->Add(EXPLOSION, "Resources/Explosion.wav", 3);
    audio->Volume(PULSE, 0.3f);
    audio->Volume(EXPLOSION, 0.2f);

    // carrega painéis e pano de fundo
    backg = new Sprite("Resources/Kamikaze.jpg");
    infoBox = new Sprite("Resources/InfoBox.png");
    keyMap = new Sprite("Resources/KeyMap.png");
    
    // cria cena com o avião
    scene = new Scene();
    scene->Add(new Plane(), STATIC);

    // calcula proporção entre a janela e o pano de fundo
    float hScale = window->Width() / 1920.0f;
    float vScale = window->Height() / 1080.0f;

    // define escala para o pano de fundo
    bgScale = hScale > vScale ? hScale : vScale;
}

// ------------------------------------------------------------------------------

void Vector2D::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualização da cena
    scene->Update();
} 

// ------------------------------------------------------------------------------

void Vector2D::Draw()
{
    // desenha pano de fundo
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, bgScale);

    // desenha elementos sobrepostos
    keyMap->Draw(window->CenterX(), window->Height() - 16.0f, Layer::UPPER);
    infoBox->Draw(120, 100, Layer::UPPER);
    
    // desenho da cena
    scene->Draw();
} 

// ------------------------------------------------------------------------------

void Vector2D::Finalize()
{
    delete scene;
    delete backg;
    delete keyMap;
    delete infoBox;
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
    engine->window->Size(1200, 640);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Vector 2D");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Vector2D());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

