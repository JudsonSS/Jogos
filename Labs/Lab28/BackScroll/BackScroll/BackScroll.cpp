/**********************************************************************************
// BackScroll (Código Fonte)
// 
// Criação:     22 Out 2012
// Atualização: 12 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Desenhando e movimentando um background maior que a janela
//
**********************************************************************************/

#include "Engine.h"
#include "BackScroll.h"

// ------------------------------------------------------------------------------

void BackScroll::Init() 
{
    // carrega fontes 
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Tahoma14b.png");
    bold->Spacing("Resources/Tahoma14b.dat");

    // carrega sprites
    infoBox = new Sprite("Resources/InfoBox.png");
    keyMap  = new Sprite("Resources/Keymap.png");
    backg   = new Background("Resources/Backg.jpg");

    // inicializa viewport para o centro do background
    viewport.left = (backg->Width() - window->Width()) / 2.0f;
    viewport.right = viewport.left + window->Width();
    viewport.top = (backg->Height() - window->Height()) / 2.0f;
    viewport.bottom = viewport.top + window->Height();

    // inicializa velocidade de rolamento da tela
    scrollSpeed = 400;

    // exibe ponto-flutuantes sem casas
    text << std::fixed;
    text.precision(0);
}

// ------------------------------------------------------------------------------

void BackScroll::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // deslocamento padrão
    float delta = scrollSpeed * gameTime;

    // movimenta viewport
    if (window->KeyDown(VK_LEFT))
    {
        viewport.left -= delta;
        viewport.right -= delta;

        if (viewport.left < 0)
        {
            viewport.left = 0;
            viewport.right = window->Width();
        }
    }

    if (window->KeyDown(VK_RIGHT))
    {
        viewport.left += delta;
        viewport.right += delta;

        if (viewport.right > backg->Width())
        {
            viewport.left = backg->Width() - window->Width();
            viewport.right = backg->Width();
        }
    }

    if (window->KeyDown(VK_UP))
    {
        viewport.top -= delta;
        viewport.bottom -= delta;

        if (viewport.top < 0)
        {
            viewport.top = 0;
            viewport.bottom = window->Height();
        }
    }

    if (window->KeyDown(VK_DOWN))
    {
        viewport.top += delta;
        viewport.bottom += delta;

        if (viewport.bottom > backg->Height())
        {
            viewport.top = backg->Height() - window->Height();
            viewport.bottom = backg->Height();
        }
    }
} 

// ------------------------------------------------------------------------------

void BackScroll::Draw()
{
    // desenha o pano de fundo
    backg->Draw(viewport);
    
    // desenha os elementos da interface
    infoBox->Draw(142, 98, Layer::FRONT);
    keyMap->Draw(window->CenterX(), window->Height() - 16.0f, Layer::FRONT);
    
    // desenha os textos
    text.str("");
    text << "Background Scrolling";
    bold->Draw(60, 70, text.str());

    text.str("");
    text << "Janela: " << window->Width() << " x " << window->Height();
    font->Draw(60, 100, text.str());

    text.str("");
    text << "Background: " << backg->Width() << " x " << backg->Height();
    font->Draw(60, 120, text.str());
    
    text.str("");
    text << "Viewport: (" << viewport.left << "," << viewport.top << ") a (" << viewport.right << "," << viewport.bottom << ")";
    font->Draw(60, 140, text.str());
    
    text.str("");
    text << "Use as setas para mover a Viewport";
    font->Draw(window->CenterX() - 82.0f, window->Height() - 7.0f, text.str());
} 

// ------------------------------------------------------------------------------

void BackScroll::Finalize()
{
    delete infoBox;
    delete keyMap;
    delete backg;
    delete font;
    delete bold;
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
    engine->window->Size(1000, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Background Scrolling");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // inicia o jogo
    int status = engine->Start(new BackScroll());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

