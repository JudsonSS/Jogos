/**********************************************************************************
// Hud (Código Fonte)
//
// Criação:     02 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Heads Up Display
//
**********************************************************************************/

#include "Hud.h"
#include "BasicAI.h"

// ------------------------------------------------------------------------------

// inicializa contadores
uint Hud::missiles = 0;
uint Hud::oranges = 0;
uint Hud::magentas = 0;
uint Hud::blues = 0;
uint Hud::greens = 0;
uint Hud::particles = 0;

// ------------------------------------------------------------------------------

Hud::Hud()
{
    // cria fonte para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Tahoma14b.png");
    bold->Spacing("Resources/Tahoma14b.dat");

    // carrega sprites
    infoBox = new Sprite("Resources/InfoBox.png");

    // inicializa contador de frames e tempo transcorrido
    frameCount = 0;
    totalTime = 0.0f;
    fps = 0;
}

// ------------------------------------------------------------------------------

Hud::~Hud()
{
    delete font;
    delete bold;
    delete infoBox;
}

// -------------------------------------------------------------------------------

void Hud::Update()
{
    // tempo acumulado dos frames
    totalTime += gameTime;

    // incrementa contador de frames
    frameCount++;

    // a cada 1000ms (1 segundo) atualiza indicador de FPS
    if (totalTime >= 1.0f)
    {
        fps = frameCount;
        frameCount = 0;
        totalTime -= 1.0f;
    }
}

// -------------------------------------------------------------------------------

void Hud::Draw()
{
    // desenha elementos da interface
    infoBox->Draw(game->viewport.left + 140, game->viewport.top + 100, Layer::FRONT);

    // define cor do texto
    Color textColor{ 0.7f, 0.7f, 0.7f, 1.0f };

    // desenha texto
    text.str("");
    text << "Geometry Wars";
    bold->Draw(40, 62, text.str(), textColor);

    text.str("");
    text << "FPS: " << fps;
    font->Draw(40, 92, text.str(), textColor);

    text.str("");
    text << "Partículas: " << particles;
    font->Draw(40, 112, text.str(), textColor);

    text.str("");
    text << "Inimigos: " << oranges + magentas + blues + greens;
    font->Draw(40, 132, text.str(), textColor);

    text.str("");
    text << "Mísseis: " << missiles;
    font->Draw(40, 152, text.str(), textColor);
}

// -------------------------------------------------------------------------------
