/**********************************************************************************
// Hud (Código Fonte)
//
// Criação:     02 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Heads Up Display
//
**********************************************************************************/

#include "Hud.h"
#include "GeoWars.h"

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
    text << "Geometry Wars";
    bold->Draw(40, 62, text.str(), textColor);

    text.str("");
    text << "Janela: " << window->Width() << " x " << window->Height();
    font->Draw(40, 92, text.str(), textColor);

    text.str("");
    text << "Mundo: " << game->Width() << " x " << game->Height();
    font->Draw(40, 112, text.str(), textColor);

    text.str("");
    text << "Viewport: (" << uint(game->viewport.left) << "," << uint(game->viewport.top) << ") a (" << uint(game->viewport.right) << "," << uint(game->viewport.bottom) << ")";
    font->Draw(40, 132, text.str(), textColor);

    text.str("");
    text << "Mísseis: " << GeoWars::scene->Size() - 5;
    font->Draw(40, 152, text.str(), textColor);

    text.str("");
    text << "Movimento";
    bold->Draw(window->CenterX() - 84.0f, window->Height() - 7.0f, text.str(), textColor);

    text.str("");
    text << "Disparo";
    bold->Draw(window->CenterX() + 115.0f, window->Height() - 7.0f, text.str(), textColor);
}

// -------------------------------------------------------------------------------
