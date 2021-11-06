/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:     23 Nov 2011
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para um míssil
//
**********************************************************************************/

#include "Missile.h"
#include "WallHit.h"
#include "WavesDemo.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

Player* & Missile::player = WavesDemo::player;        // referência para o player

// ------------------------------------------------------------------------------

Missile::Missile()
{
    // inicializa sprite
    sprite = new Sprite("Resources/Missile.png");

    // cria bounding box
    BBox(new Circle(8));

    // inicializa velocidade
    speed.RotateTo(player->speed->Angle());
    speed.ScaleTo(15.0f);
    
    // move para posição
    MoveTo(player->X() + 22 * cos(speed.Radians()), player->Y() - 22 * sin(speed.Radians()));
    RotateTo(-player->speed->Angle() + 90.0f);

    // define tipo
    type = MISSILE;

    // incrementa contagem
    ++Hud::missiles;
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
    delete sprite;

    // decrementa contagem
    --Hud::missiles;
}

// -------------------------------------------------------------------------------

void Missile::Update()
{
    // move míssel com vetor resultante
    Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

    // remove míssil da cena se ele sair da área de jogo
    if (x > game->Width() || x < 0 || y > game->Height() || y < 0)
    {
        // volume do som de destruição depende da distância para o jogador
        const float MaxDistance = 4406;
        const float BaseVolume = 0.8f;
        float distance = Point::Distance(Point(x, y), Point(player->X(), player->Y()));
        float level = (MaxDistance - distance) / MaxDistance * BaseVolume;
        WavesDemo::audio->Volume(HITWALL, level);
        WavesDemo::audio->Play(HITWALL);

        // adiciona explosão na cena
        WavesDemo::scene->Add(new WallHit(x,y), STATIC);

        // remove míssil da cena
        WavesDemo::scene->Delete();
    }
}

// -------------------------------------------------------------------------------
