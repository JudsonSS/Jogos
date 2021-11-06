/**********************************************************************************
// Wave (Código Fonte)
//
// Criação:     06 Ago 2019
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos
//
**********************************************************************************/

#include "Wave.h"
#include "ChaseDemo.h"
#include "Magenta.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

Wave::Wave() : posX(0, window->Width()), posY(0, window->Height()), secs(2.0f, 4.0f)
{
    // posição dos inimigos
    pX = posX.Rand();
    pY = posY.Rand();

    // atraso para a próxima onda 
    delay = secs.Rand();
}

// ------------------------------------------------------------------------------

Wave::~Wave()
{

}

// -------------------------------------------------------------------------------

void Wave::Update()
{
    // se passou o tempo mínimo entre ondas
    if (timer.Elapsed(delay) && Hud::enemies < 15)
    {
        // toca som de nova onda
        ChaseDemo::audio->Play(SPAWN);

        // adiciona novo inimigo
        ChaseDemo::scene->Add(new Magenta(pX, pY, ChaseDemo::player), MOVING);

        // nova posição do inimigo
        pX = posX.Rand();
        pY = posY.Rand();

        // nova onda
        ++Hud::waves;

        // reinicia o timer
        timer.Start();
    }
}

// -------------------------------------------------------------------------------

void Wave::Draw()
{
    
}

// -------------------------------------------------------------------------------
