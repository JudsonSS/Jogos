/**********************************************************************************
// TiledScroll (Código Fonte)
//
// Criação:     22 Out 2012
// Atualização: 12 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Desenhando e movimentando um background formado por blocos
//
**********************************************************************************/

#include "Engine.h"
#include "TiledScroll.h"

// ------------------------------------------------------------------------------

void TiledScroll::Init()
{
    int MapData[30 * 20] =
    {
        81, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 5, 79, 158, 38,
        91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 48, 79, 158, 38,
        91, 4, 114, 52, 4, 4, 4, 114, 4, 14, 96, 4, 4, 4, 52, 114, 4, 4, 4, 4, 4, 64, 4, 114, 4, 107, 58, 59, 158, 38,
        91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 52, 4, 4, 4, 4, 4, 107, 56, 58, 158, 158, 38,
        91, 4, 96, 4, 4, 102, 102, 102, 102, 102, 102, 113, 4, 4, 4, 4, 4, 4, 114, 4, 4, 4, 4, 107, 96, 77, 79, 158, 19, 38,
        91, 4, 4, 4, 93, 1, 2, 2, 2, 2, 3, 101, 4, 4, 4, 4, 137, 4, 4, 4, 4, 84, 107, 77, 77, 77, 68, 158, 158, 38,
        91, 4, 4, 93, 44, 11, 72, 71, 34, 72, 13, 111, 91, 4, 4, 4, 4, 114, 114, 4, 4, 4, 87, 77, 135, 77, 77, 68, 156, 38,
        91, 4, 4, 93, 111, 11, 33, 72, 72, 72, 13, 111, 91, 4, 4, 4, 4, 4, 4, 4, 14, 4, 4, 87, 77, 77, 77, 48, 158, 38,
        91, 4, 4, 93, 111, 11, 72, 72, 71, 12, 72, 3, 91, 4, 4, 4, 96, 4, 4, 4, 4, 24, 4, 4, 87, 77, 48, 158, 158, 38,
        91, 4, 4, 93, 123, 21, 72, 71, 72, 72, 72, 72, 3, 91, 4, 4, 4, 4, 4, 4, 4, 4, 114, 4, 64, 4, 93, 28, 29, 38,
        91, 96, 4, 93, 111, 83, 11, 41, 42, 42, 42, 43, 13, 91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 113, 82, 82, 83,
        91, 96, 96, 4, 4, 93, 11, 61, 62, 62, 62, 63, 13, 101, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 137, 4, 4, 93,
        91, 4, 114, 4, 4, 93, 21, 22, 22, 22, 22, 22, 23, 31, 101, 4, 4, 138, 136, 4, 4, 96, 132, 4, 4, 137, 4, 4, 4, 93,
        91, 4, 4, 4, 4, 113, 82, 82, 82, 82, 82, 82, 83, 32, 32, 91, 4, 138, 136, 4, 4, 4, 4, 4, 4, 4, 4, 137, 4, 93,
        91, 4, 114, 52, 4, 4, 4, 4, 4, 14, 4, 114, 93, 31, 32, 101, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 93,
        91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 83, 32, 32, 91, 4, 4, 4, 4, 4, 52, 4, 104, 114, 104, 4, 4, 93,
        91, 4, 4, 4, 4, 4, 114, 114, 4, 4, 4, 4, 4, 93, 31, 32, 101, 4, 114, 4, 4, 4, 4, 4, 62, 62, 62, 4, 4, 93,
        91, 4, 4, 4, 4, 96, 4, 4, 4, 96, 4, 4, 4, 4, 83, 32, 32, 91, 4, 4, 14, 4, 4, 4, 43, 112, 41, 4, 4, 93,
        91, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 92, 93, 31, 32, 91, 4, 113, 92, 4, 4, 4, 132, 42, 4, 4, 4, 93,
        101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 113, 93, 32, 32, 91, 93, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 103
    };

    // carrega pano de fundo
    tiles = new Image("Resources/GroundTiles.bmp", 64, 64, 16, MapData, 30, 20);
    backg = new Background(tiles);

    // carrega sprites
    infoBox = new Sprite("Resources/InfoBox.png");
    keyMap  = new Sprite("Resources/Keymap.png");

    // carrega fontes
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Tahoma14b.png");
    bold->Spacing("Resources/Tahoma14b.dat");

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

void TiledScroll::Update()
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

void TiledScroll::Draw()
{
    // desenha o pano de fundo
    backg->Draw(viewport);
    
    // desenha elementos da interface
    infoBox->Draw(142, 98, 0.2f);
    keyMap->Draw(window->CenterX(), window->Height() - 16.0f, 0.2f);
    
    // desenha texto
    text.str("");
    text << "Tiled Map";
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

void TiledScroll::Finalize()
{
    delete infoBox;
    delete keyMap;
    delete tiles;
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
    engine->window->Title("Tiled Map");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // inicia o jogo
    engine->Start(new TiledScroll());

    delete engine;
    return 0;
}

// ----------------------------------------------------------------------------

