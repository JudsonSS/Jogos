/**********************************************************************************
// Orange (Código Fonte)
// 
// Criação:     05 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz movimento retilíneo
//
**********************************************************************************/

#include "GeoWars.h"
#include "Orange.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Orange::Orange(Player * p) : player (p)
{
    sprite = new Sprite("Resources/Orange.png");
    speed  = new Vector(0, 2.0f);
    BBox(new Circle(20.0f));

    // ajusta ângulo do vetor na direção do jogador
    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    RotateTo(-speed->Angle());
    
    // move para uma posição aleatória (canto superior esquerdo)
    RandF pos{ 100, 150 };
    MoveTo(pos.Rand(), pos.Rand());

    multiplier = 70.0f;
    type = ORANGE;

    // configuração do emissor de partículas
    Generator emitter;
    emitter.imgFile = "Resources/Spark.png";    // arquivo de imagem
    emitter.angle = speed->Angle() + 180;       // ângulo base do emissor
    emitter.spread = 10;                        // espalhamento em graus
    emitter.lifetime = 0.2f;                    // tempo de vida em segundos
    emitter.frequency = 0.010f;                 // tempo entre geração de novas partículas
    emitter.percentToDim = 0.7f;                // desaparece após 60% da vida
    emitter.minSpeed = 50.0f;                   // velocidade mínima das partículas
    emitter.maxSpeed = 100.0f;                  // velocidade máxima das partículas
    emitter.color.r = 1.0f;                     // componente Red da partícula 
    emitter.color.g = 0.5;                      // componente Green da partícula 
    emitter.color.b = 0.0f;                     // componente Blue da partícula 
    emitter.color.a = 1.0f;                     // transparência da partícula

    // cria sistema de partículas
    tail = new Particles(emitter);
}

// ---------------------------------------------------------------------------------

Orange::~Orange()
{
    delete sprite;
    delete speed;
    delete tail;
}

// -------------------------------------------------------------------------------

void Orange::OnCollision(Object * obj)
{
    if (obj->Type() == MISSILE)
        GeoWars::scene->Delete(this, MOVING);
}

// -------------------------------------------------------------------------------

void Orange::Update()
{
    // movimenta objeto pelo seu vetor velocidade
    Translate(speed->XComponent() * multiplier * gameTime, -speed->YComponent() * multiplier * gameTime);

    // ajusta ângulo do vetor na direção do jogador
    if (x < 100 || y < 100 || x > game->Width() - 100 || y > game->Height() - 100)
    {
        multiplier = 200;
        speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
        RotateTo(-speed->Angle());
    }

    // atualiza calda da nave
    tail->Config().angle = speed->Angle();
    tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
    tail->Update(gameTime);
}

// ---------------------------------------------------------------------------------

void Orange::Draw()
{
    sprite->Draw(x, y, Layer::LOWER, scale, rotation);
    tail->Draw(Layer::LOWER, 1.0f);
}

// -------------------------------------------------------------------------------