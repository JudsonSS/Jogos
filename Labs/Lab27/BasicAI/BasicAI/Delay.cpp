/**********************************************************************************
// Delay (Código Fonte)
//
// Criação:     02 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Sincroniza uma ação
//
**********************************************************************************/

#include "Delay.h"
#include "BasicAI.h"
#include "WaveO.h"
#include "WaveM.h"
#include "WaveB.h"
#include "WaveG.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

Delay::Delay()
{
    logo = new Sprite("Resources/Logo.png");
    timer.Start();

    notPlayed = true;
    fase1 = false;
    fase2 = false;
    fase3 = false;
    fase4 = false;
}

// ------------------------------------------------------------------------------

Delay::~Delay()
{
    delete logo;
}

// -------------------------------------------------------------------------------

void Delay::Update()
{
    if (notPlayed && timer.Elapsed(2.0f))
    {
        // toca áudio de introdução
        BasicAI::audio->Play(START);
        notPlayed = false;
    }

    if (!fase1 && timer.Elapsed(6.0f))
    {
        // toca música do jogo
        BasicAI::audio->Play(THEME, true);
        BasicAI::scene->Add(new WaveO(), STATIC);
        BasicAI::viewHUD = true;
        fase1 = true;
    }

    if (!fase2 && timer.Elapsed(8.0f))
    {
        BasicAI::scene->Add(new WaveM(), STATIC);
        fase2 = true;
    }

    if (!fase3 && timer.Elapsed(10.0f))
    {
        BasicAI::scene->Add(new WaveB(), STATIC);
        fase3 = true;
    }

    if (!fase4 && timer.Elapsed(15.0f))
    {
        BasicAI::scene->Add(new WaveG(), STATIC);
        BasicAI::scene->Delete();
        fase4 = true;
    }
}

// -------------------------------------------------------------------------------

void Delay::Draw()
{
    if (!fase1)
        logo->Draw(game->viewport.left + window->CenterX() , game->viewport.top + window->CenterY(), Layer::FRONT);
}

// -------------------------------------------------------------------------------
