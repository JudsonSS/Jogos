/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:     07 Fev 2013
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Mísseis usados em SoundDist
//
**********************************************************************************/

#include "SoundDist.h"
#include "Missile.h"
#include "Explosion.h"

// ---------------------------------------------------------------------------------

Missile::Missile(Image * img, TileSet * explosion)
{
    explodSet = explosion;
    sprite = new Sprite(img);
    BBox(new Point(x, y));
    vel = 400;
}

// ---------------------------------------------------------------------------------

Missile::~Missile()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Missile::OnCollision(Object * obj)
{
    // toca som de explosão
    SoundDist::audio->Volume(EXPLOSION, y / window->Height());
    SoundDist::audio->Play(EXPLOSION);

    // inica animação de explosão
    Explosion * explo = new Explosion(explodSet);
    explo->MoveTo(x, y, Layer::FRONT);
    SoundDist::scene->Add(explo, STATIC);

    // remove míssil da cena
    SoundDist::scene->Delete(this, MOVING);
}

// ---------------------------------------------------------------------------------

void Missile::Update()
{
    // objeto se move no eixo y
    Translate(0, -vel * gameTime);

    // remove mísseis que saem da janela
    if (Y() < 0)
        SoundDist::scene->Delete();
}

// ---------------------------------------------------------------------------------
