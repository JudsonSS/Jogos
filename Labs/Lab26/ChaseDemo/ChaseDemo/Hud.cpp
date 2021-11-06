/**********************************************************************************
// Hud (Código Fonte)
//
// Criação:     02 Ago 2019
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Heads Up Display
//
**********************************************************************************/

#include "Hud.h"
#include "ChaseDemo.h"

// ------------------------------------------------------------------------------

// inicializa contadores
uint Hud::missiles = 0;
uint Hud::enemies = 0;
uint Hud::waves = 0;

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
    keyMap = new Sprite("Resources/Keymap.png");
}

// ------------------------------------------------------------------------------

Hud::~Hud()
{
    delete font;
    delete bold;
    delete infoBox;
    delete keyMap;
}

// -------------------------------------------------------------------------------

void Hud::Update()
{
}

// -------------------------------------------------------------------------------

void Hud::Draw()
{
    // desenha elementos da interface
    infoBox->Draw(game->viewport.left + 140, game->viewport.top + 100, Layer::FRONT);
    keyMap->Draw(game->viewport.left + window->CenterX(), game->viewport.top + window->Height() - 16.0f, Layer::FRONT);

    // define cor do texto
    Color textColor{ 0.7f, 0.7f, 0.7f, 1.0f };

    // desenha texto
    text.str("");
    text << "Chase Demo";
    bold->Draw(40, 62, text.str(), textColor);

    text.str("");
    text << "Janela: " << window->Width() << " x " << window->Height();
    font->Draw(40, 92, text.str(), textColor);

    text.str("");
    text << "Ondas: " << waves;
    font->Draw(40, 112, text.str(), textColor);

    text.str("");
    text << "Inimigos: " << enemies;
    font->Draw(40, 132, text.str(), textColor);

    text.str("");
    text << "Mísseis: " << missiles;
    font->Draw(40, 152, text.str(), textColor);

    text.str("");
    text << "Movimento";
    bold->Draw(window->CenterX() - 84.0f, window->Height() - 7.0f, text.str(), textColor);

    text.str("");
    text << "Disparo";
    bold->Draw(window->CenterX() + 115.0f, window->Height() - 7.0f, text.str(), textColor);
}

// -------------------------------------------------------------------------------
