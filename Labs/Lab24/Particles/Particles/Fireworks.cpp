/**********************************************************************************
// Fireworks (Código Fonte)
// 
// Criação:     17 Mar 2013
// Atualização: 27 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#include "Refinery.h"
#include "Fireworks.h"

// ---------------------------------------------------------------------------------

Fireworks::Fireworks()
{
    // configura gerador de partículas
    Generator starmaker;
    starmaker.imgFile = "Resources/Star.png";   // arquivo de imagem
    starmaker.angle = RandAngle(mt);            // direção das estrelas
    starmaker.spread = 360.0f;                  // espalhamento em graus
    starmaker.lifetime = 2.0f;                  // tempo de vida (em segundos)
    starmaker.frequency = 0.000f;               // tempo entre geração de novas partículas
    starmaker.percentToDim = 0.6f;              // desaparece após 60% da vida
    starmaker.minSpeed = 25.0f;                 // velocidade mínima das partículas
    starmaker.maxSpeed = 250.0f;                // velocidade máxima das partículas
    starmaker.color.r = RandColor(mt);          // cor aleatória para partícula
    starmaker.color.g = RandColor(mt);          // cor aleatória para partícula
    starmaker.color.b = RandColor(mt);          // cor aleatória para partícula
    starmaker.color.a = 1.0f;                   // transparência da partícula

    // cria sistema de partículas
    starGen = new Particles(starmaker);

    // gera 50 partículas na posição do mouse
    starGen->Generate(window->MouseX(), window->MouseY(), 50);
    type = FIREWORKS;
}

// ---------------------------------------------------------------------------------

Fireworks::~Fireworks()
{
    delete starGen;
}

// -------------------------------------------------------------------------------

void Fireworks::Update()
{
    // atualiza posição de cada partícula
    starGen->Update(gameTime);

    // remove da cena quando todas as partículas estão inativas
    if (starGen->Inactive())
        Refinery::scene->Delete();
}

// -------------------------------------------------------------------------------