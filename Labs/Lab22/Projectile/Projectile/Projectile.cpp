/**********************************************************************************
// Projectile (Código Fonte)
// 
// Criação:     01 Out 2012
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Movimento de projétil

**********************************************************************************/

#include "Engine.h"
#include "Projectile.h"
#include "Ball.h"

// ------------------------------------------------------------------------------

Scene * Projectile::scene = nullptr;            // cena do jogo
Audio * Projectile::audio = nullptr;            // sistema de áudio
Font  * Projectile::font  = nullptr;            // fonte para texto

// ------------------------------------------------------------------------------

void Projectile::Init() 
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(CANNON, "Resources/Cannon.wav", 5);
    audio->Add(SPLASH, "Resources/WaterSplash.wav", 10);
    audio->Volume(CANNON, 0.5f);            
    audio->Volume(SPLASH, 0.2f);
    
    // cria fontes para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");

    // cria cena do jogo
    scene = new Scene();
    cannon = new Cannon();
    scene->Add(cannon, STATIC);
    
    backg   = new Sprite("Resources/Sky.png");
    infoBox = new Sprite("Resources/InfoBox.png");
    keyMap  = new Sprite("Resources/Keymap.png");
}

// ------------------------------------------------------------------------------

void Projectile::Update()
{
    // sai com o pressionamento de ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza a cena
    scene->Update();
} 

// ------------------------------------------------------------------------------

void Projectile::Draw()
{
    // desenha pano de fundo 
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    // desenha elementos sobrepostos
    keyMap->Draw(window->CenterX(), window->Height() - 16.0f, Layer::UPPER);
    infoBox->Draw(870, 100, Layer::UPPER);

    // desenha cena
    scene->Draw();

    // define cor do texto
    Color textColor{ 0.65f, 0.65f, 0.65f, 1.0f };

    // desenha texto
    text.str("");
    text << "Movimento de Projétil";
    font->Draw(815, 65, text.str(), textColor);

    text.str("");
    text << "Resistência do ar: " << (Ball::airResistance ? "Ligado" : "Desligado");
    font->Draw(815, 105, text.str(), textColor);

    text.str("");
    text << "Ângulo do Canhão: " << int(cannon->direction.Angle()) << "°";
    font->Draw(815, 125, text.str(), textColor);

    text.str("");
    text << "Projéteis ativos: " << scene->Size() - 1;
    font->Draw(815, 145, text.str(), textColor);
} 

// ------------------------------------------------------------------------------

void Projectile::Finalize()
{
    delete backg;
    delete keyMap;
    delete infoBox;
    delete scene;
    delete audio;
    delete font;
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
    engine->window->Size(1024,600);
    engine->window->Color(25, 25, 25);
    engine->window->Title("Projectile");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    // engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Projectile());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

