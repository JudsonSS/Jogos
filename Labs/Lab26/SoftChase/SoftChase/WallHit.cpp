/**********************************************************************************
// WallHit (Código Fonte)
// 
// Criação:     03 Ago 2019
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#include "SoftChase.h"
#include "WallHit.h"
#include "Random.h"

// ---------------------------------------------------------------------------------

WallHit::WallHit(float pX, float pY)
{
    // calcula ângulo base e ajusta coordenadas da explosão
    float base;
    if (pX < 0)
    {
        base = 0.0f;
        pX = 0;
    }
    else if (pX > game->Width())
    {
        base = 180.0f;
        pX = game->Width();
    }
    else if (pY < 0)
    {
        base = 270.0f;
        pY = 0;
    }
    else
    {
        base = 90.0f;
        pY = game->Height();
    }

    // número aleatório entre 0 e 1
    RandF color{ 0, 1 };
    
    // configura emissor de partículas
    Generator explosion;
    explosion.imgFile   = "Resources/Spark.png";    // arquivo de imagem
    explosion.angle     = base;                     // direção da explosão
    explosion.spread    = 160.0f;                   // espalhamento em graus
    explosion.lifetime  = 1.0f;                     // tempo de vida em segundos
    explosion.frequency = 0.000f;                   // tempo entre geração de novas partículas
    explosion.percentToDim = 0.6f;                  // desaparece após 60% da vida
    explosion.minSpeed  = 25.0f;                    // velocidade mínima das partículas
    explosion.maxSpeed  = 250.0f;                   // velocidade máxima das partículas
    explosion.color.r   = color.Rand();             // cor da partícula entre 0 e 1
    explosion.color.g   = color.Rand();             // cor da partícula entre 0 e 1
    explosion.color.b   = color.Rand();             // cor da partícula entre 0 e 1
    explosion.color.a   = 1.0f;                     // transparência da partícula

    // cria sistema de partículas
    sparks = new Particles(explosion);

    // gera 25 partículas na posição de contato
    sparks->Generate(pX, pY, 25);
    type = WALLHIT;
}

// ---------------------------------------------------------------------------------

WallHit::~WallHit()
{
    delete sparks;
}

// -------------------------------------------------------------------------------

void WallHit::Update()
{
    // atualiza posição de cada partícula
    sparks->Update(gameTime);

    // remove da cena quando todas as partículas estão inativas
    if (sparks->Inactive())
        SoftChase::scene->Delete();
}

// -------------------------------------------------------------------------------