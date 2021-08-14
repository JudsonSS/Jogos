/**********************************************************************************
// SpriteDemo
// 
// Criação:     09 Mai 2014
// Atualização: 14 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   O programa carrega e desenha imagens opacas e transparentes,
//              demonstrando como usar as classes Image e Sprite com os novos
//              recursos de desenho de Sprites da classe Renderer
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

class SpriteDemo : public Game
{
private:
    Sprite * backg   = nullptr;            // sprite do fundo de tela
    Sprite * shank   = nullptr;            // sprite do personagem 

    Image  * logoImg = nullptr;            // imagem do logotipo
    Sprite * logo1   = nullptr;            // sprite 1 do logotipo
    Sprite * logo2   = nullptr;            // sprite 2 do logotipo

    float x = 0, y = 0;                    // posição x,y do shank

public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

// ------------------------------------------------------------------------------

void SpriteDemo::Init()
{
    backg = new Sprite("Resources/Background.jpg");
    shank = new Sprite("Resources/Shank.png");

    logoImg = new Image("Resources/Logo.png");
    logo1 = new Sprite(logoImg);
    logo2 = new Sprite(logoImg);

    x = 80.0f;
    y = 90.0f;
}

// ------------------------------------------------------------------------------

void SpriteDemo::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // desloca personagem
    if (window->KeyDown(VK_LEFT))
        x -= 50.0f * gameTime;
    if (window->KeyDown(VK_RIGHT))
        x += 50.0f * gameTime;
    if (window->KeyDown(VK_UP))
        y -= 50.0f * gameTime;
    if (window->KeyDown(VK_DOWN))
        y += 50.0f * gameTime;
} 

// ------------------------------------------------------------------------------

void SpriteDemo::Draw()
{
    backg->Draw(0.0f, 0.0f, Layer::BACK);
    shank->Draw(x, y);
    logo1->Draw(40.0f, 60.0f, Layer::UPPER);
    logo2->Draw(400.0f, 450.0f, Layer::LOWER);
}

// ------------------------------------------------------------------------------

void SpriteDemo::Finalize()
{
    // remove sprites da memória
    delete backg;
    delete shank;
    delete logo1;
    delete logo2;

    // remove imagem da memória
    delete logoImg;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor de jogo
    Engine * engine = new Engine();
    
    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Sprite Demo");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new SpriteDemo());

    // destrói o motor e o jogo
    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

