/**********************************************************************************
// Wave (Código Fonte)
//
// Criação:     06 Ago 2019
// Atualização: 05 Ago 2019
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria uma onda de inimigos
//
**********************************************************************************/

#include "Wave.h"
#include "RunDemo.h"
#include "Green.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

Wave::Wave() : secs(8.0f, 10.0f)
{
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
    // contador de inimigos
    static uint counter = 8;

    // se passou o tempo de atraso
    if (timer.Elapsed(delay) && Hud::enemies < 24)
    {
        if (counter > 0)
        {
            // toca som de nova onda
            RunDemo::audio->Play(SPAWN);

            // adiciona nova inimigo
            RunDemo::scene->Add(new Green(0, 0, RunDemo::player), MOVING);
            RunDemo::scene->Add(new Green(window->Width(), 0, RunDemo::player), MOVING);
            RunDemo::scene->Add(new Green(window->Width(), window->Height(), RunDemo::player), MOVING);
            RunDemo::scene->Add(new Green(0, window->Height(), RunDemo::player), MOVING);

            delay = 0.450f;
            timer.Start();
            --counter;
        }
        else
        {
            // nova onda
            ++Hud::waves;
            counter = 8;
            delay = secs.Rand();
            timer.Start();
        }
    }
}

// -------------------------------------------------------------------------------

void Wave::Draw()
{
    
}

// -------------------------------------------------------------------------------
