/**********************************************************************************
// Smoke (Código Fonte)
// 
// Criação:     17 Mar 2013
// Atualização: 27 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Efeito de fumaça usando sistema de partículas
//
**********************************************************************************/

#include "Smoke.h"
#include "Refinery.h"

// ---------------------------------------------------------------------------------

Smoke::Smoke(float pX, float pY, float angle, bool night)
{
    // configura gerador de partículas
    Generator fogger;
    fogger.imgFile   = "Resources/Smoke.png";    // arquivo de imagem
    fogger.angle     = angle;                    // direção da fumaça
    fogger.spread    = 30;                       // espalhamento em graus
    fogger.lifetime  = 1.0f;                     // tempo de vida em segundos
    fogger.frequency   = 0.010f;                 // tempo entre geração de novas partículas
    fogger.percentToDim = 0.60f;                 // desaparece após 60% da vida
    fogger.minSpeed  = 75.0f;                    // velocidade mínima das partículas
    fogger.maxSpeed  = 100.0f;                   // velocidade máxima das partículas

    // cor da partícula depende da iluminação
    if (night)
    {
        fogger.color.r = 0.2f;                   // cor da partícula
        fogger.color.g = 0.2f;                   // cor da partícula
        fogger.color.b = 0.2f;                   // cor da partícula
        fogger.color.a = 1.0f;                   // cor da partícula
    }
    else
    {
        fogger.color.r = 1.0f;                   // cor da partícula
        fogger.color.g = 1.0f;                   // cor da partícula
        fogger.color.b = 1.0f;                   // cor da partícula
        fogger.color.a = 1.0f;                   // cor da partícula
    }

    // cria sistema de partículas
    smokeGen = new Particles(fogger);
    MoveTo(pX, pY);
    stop = false;
    type = SMOKE;
}

// ---------------------------------------------------------------------------------

Smoke::~Smoke()
{
    delete smokeGen;
}

// -------------------------------------------------------------------------------

void Smoke::TurnOff()
{
    stop = true;
}

// -------------------------------------------------------------------------------

void Smoke::Update()
{
    if (stop)
    {
        if (smokeGen->Inactive())
            Refinery::scene->Delete();
    }
    else
    {
        smokeGen->Generate(x, y);
    }

    smokeGen->Update(gameTime);
}

// -------------------------------------------------------------------------------
