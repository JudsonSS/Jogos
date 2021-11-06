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
#include "WavesDemo.h"
#include "Orange.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

Wave::Wave() : position(0, 3), delay (1.0f, 5.0f)
{
    // calcula número de inimigos que cabem na largura e na altura da tela
    numX = int(window->Width() / 50) - 1;
    numY = int(window->Height() / 50) - 1;
    
    // posição dos inimigos
    posX = 0;
    posY = 0;

    // não enviar nova onda agora
    newWave = false;
    waveDelay = delay.Rand();
}

// ------------------------------------------------------------------------------

Wave::~Wave()
{

}

// -------------------------------------------------------------------------------

void Wave::Update()
{
    // nova onda foi solicitada
    if (newWave)
    {
        // se passou o tempo mínimo entre ondas
        if (timer.Elapsed(waveDelay))
        {
            // toca som de nova onda
            WavesDemo::audio->Play(SPAWN);

            // origem da onda é aleatória
            switch (position.Rand())
            {
            case 0:
                // lado esquerdo da tela
                posY = 50;
                for (int i = 0; i < numY; ++i)
                {
                    WavesDemo::scene->Add(new Orange(0, posY, 0), MOVING);
                    posY += 50;
                }
                break;
            case 1:
                // lado superior da tela
                posX = 50;
                for (int i = 0; i < numX; ++i)
                {
                    WavesDemo::scene->Add(new Orange(posX, 0, 270), MOVING);
                    posX += 50;
                }
                break;
            case 2:
                // lado direito da tela
                posY = 50;
                for (int i = 0; i < numY; ++i)
                {
                    WavesDemo::scene->Add(new Orange(window->Width(), posY, 180), MOVING);
                    posY += 50;
                }
                break;
            case 3:
                // lado inferior da tela
                posX = 50;
                for (int i = 0; i < numX; ++i)
                {
                    WavesDemo::scene->Add(new Orange(posX, window->Height(), 90), MOVING);
                    posX += 50;
                }
                break;
            }

            // incrementa contador de ondas
            ++Hud::waves;

            // onda enviada
            newWave = false;
        }
    }
    else
    {
        // solicita nova onda se existirem poucos inimigos
        if (Hud::enemies < 10)
        {
            waveDelay = delay.Rand();
            timer.Start();
            newWave = true;
        }
    }
}

// -------------------------------------------------------------------------------

void Wave::Draw()
{
    
}

// -------------------------------------------------------------------------------
