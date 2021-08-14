/**********************************************************************************
// ShankDemo
//
// Criação:     20 Set 2011
// Atualização: 14 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   O programa testa a nova organização dos sprites 
//              através da classe base Object.
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Resources.h"
#include "Shank.h"

// ------------------------------------------------------------------------------

class ShankDemo : public Game
{
private:
    Image  * img     = nullptr;        // imagem do logotipo
    Sprite * backg   = nullptr;        // sprite para fundo da cena
    Sprite * logo1   = nullptr;        // sprite do logotipo
    Sprite * logo2   = nullptr;        // sprite do logotipo
    Shank  * shank   = nullptr;        // objeto do personagem shank

public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

// ------------------------------------------------------------------------------

void ShankDemo::Init()
{
    // inicializa objetos do jogo
    img = new Image("Resources/Logo.png");

    logo1 = new Sprite(img);
    logo2 = new Sprite(img);
    backg = new Sprite("Resources/Background.jpg");

    shank = new Shank();
}

// ------------------------------------------------------------------------------

void ShankDemo::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    shank->Update();
} 

// ------------------------------------------------------------------------------

void ShankDemo::Draw()
{
    // desenha objetos
    backg->Draw(0.0f, 0.0f, Layer::BACK);
    logo1->Draw(40.0f, 60.0f, Layer::UPPER);
    logo2->Draw(400.0f, 450.0f, Layer::LOWER);

    shank->Draw();
}

// ------------------------------------------------------------------------------

void ShankDemo::Finalize()
{
    // remove objetos da memória
    delete img;
    delete backg;    
    delete logo1;
    delete logo2;

    delete shank;
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
    engine->window->Title("Shank Demo");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new ShankDemo());

    // destrói o motor e o jogo
    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

