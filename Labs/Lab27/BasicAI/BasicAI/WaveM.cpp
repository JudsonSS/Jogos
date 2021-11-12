/**********************************************************************************
// WaveM (Código Fonte)
//
// Criação:     06 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos Magenta
//
**********************************************************************************/

#include "WaveM.h"
#include "BasicAI.h"
#include "Magenta.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

WaveM::WaveM() : posX(50, window->Width()-50), posY(50, game->Height()-50), secs(2.0f, 4.0f)
{
    // posição dos inimigos
    pX = posX.Rand();
    pY = posY.Rand();

    // atraso para a próxima onda 
    delay = secs.Rand();
}

// ------------------------------------------------------------------------------

WaveM::~WaveM()
{

}

// -------------------------------------------------------------------------------

void WaveM::Update()
{
    // se passou o tempo de atraso
    if (timer.Elapsed(delay) && Hud::magentas < 5)
    {
        // toca som de nova onda
        BasicAI::audio->Play(MAGENTA);

        // adiciona novo inimigo
        BasicAI::scene->Add(new Magenta(pX, pY, BasicAI::player), MOVING);

        // nova posição do inimigo
        pX = posX.Rand();
        pY = posY.Rand();

        // reinicia o timer
        timer.Start();
    }
}

// -------------------------------------------------------------------------------

void WaveM::Draw()
{
    
}

// -------------------------------------------------------------------------------
