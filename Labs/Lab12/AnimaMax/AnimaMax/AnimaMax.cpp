/**********************************************************************************
// AnimaMax (Código Fonte)
// 
// Criação:     10 Abr 2012
// Atualização: 27 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de uso da classe Animation
//
**********************************************************************************/

#include "Engine.h"
#include "AnimaMax.h"
#include "Explosion.h"
#include "Resources.h"

// -----------------------------------------------------------------------------

Scene * AnimaMax::scene = nullptr;

// -----------------------------------------------------------------------------

void AnimaMax::Init()
{
    scene   = new Scene();
    text    = new Sprite("Resources/TextBar.png");
    backg   = new Sprite("Resources/Background.jpg");
    tileset = new TileSet("Resources/Explosion.png", 192, 192, 5, 25);
    keyCtrl = false;
}

// ------------------------------------------------------------------------------

void AnimaMax::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // gera explosões de forma contínua com a BARRA DE ESPAÇOS
    if (window->KeyDown(VK_SPACE))
    {
        Explosion * explo = new Explosion(tileset);
        explo->MoveTo(randWidth(mt), randHeight(mt));
        scene->Add(explo, STATIC);
    } 

    // gera uma explosão com cada pressionamento do ENTER
    if (keyCtrl && window->KeyDown(VK_RETURN))
    {
        Explosion * explo = new Explosion(tileset);
        explo->MoveTo(randWidth(mt), randHeight(mt));
        scene->Add(explo, STATIC);
        keyCtrl = false;
    }
    else if (window->KeyUp(VK_RETURN))
    {
        keyCtrl = true;
    }

    // atualização da cena
    scene->Update();
} 

// ------------------------------------------------------------------------------

void AnimaMax::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    text->Draw(window->CenterX(), window->CenterY() + 45.0f);
    scene->Draw();
} 

// ------------------------------------------------------------------------------

void AnimaMax::Finalize()
{
    delete text;
    delete backg;
    delete tileset;
    delete scene;
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
    engine->window->Size(960, 540);
    engine->window->Color(0, 0, 0);
    engine->window->Title("AnimaMax");
    engine->window->Icon(IDI_ICON);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    int status = engine->Start(new AnimaMax());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

