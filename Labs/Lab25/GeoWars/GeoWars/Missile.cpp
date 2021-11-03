/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:     23 Nov 2011
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para um míssil
//
**********************************************************************************/

#include "Missile.h"
#include "WallHit.h"
#include "GeoWars.h"

// ------------------------------------------------------------------------------

Player* & Missile::player = GeoWars::player;        // referência para o player

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
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Missile::Update()
{
    // move míssel com vetor resultante
    Translate(speed.XComponent() * 90.0f * gameTime, -speed.YComponent() * 90.0f * gameTime);

    // remove míssil da cena se ele sair da área de jogo
    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
    {
        // volume do som de destruição depende da distância para o jogador
        float distance = Point::Distance(Point(x, y), Point(player->X(), player->Y()));
        float level = (MaxDistance - distance) / MaxDistance * BaseVolume;
        GeoWars::audio->Volume(HITWALL, level);
        GeoWars::audio->Play(HITWALL);

        // adiciona explosão na cena
        GeoWars::scene->Add(new WallHit(x,y), STATIC);

        // remove míssil da cena
        GeoWars::scene->Delete();
    }
}

// -------------------------------------------------------------------------------
