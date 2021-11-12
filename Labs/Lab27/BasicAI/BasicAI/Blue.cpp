/**********************************************************************************
// Blue (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz uma perseguição suavizada
//
**********************************************************************************/

#include "BasicAI.h"
#include "Blue.h"
#include "Random.h" 
#include "Hud.h"
#include "Explosion.h"

// ---------------------------------------------------------------------------------

Blue::Blue(float pX, float pY, Player* p)
{
    player = p;
    sprite = new Sprite(BasicAI::blue);
    BBox(new Circle(20.0f));
    speed.RotateTo(0.0f);
    speed.ScaleTo(0.0f);
    MoveTo(pX, pY);
    factor = -0.25f;
    type = BLUE;

    // incrementa contador
    ++Hud::blues;
}

// ---------------------------------------------------------------------------------

Blue::~Blue()
{
    delete sprite;

    // decrementa contador
    --Hud::blues;
}

// -------------------------------------------------------------------------------

void Blue::OnCollision(Object * obj)
{
    if (obj->Type() == MISSILE)
    {
        BasicAI::scene->Delete(obj, STATIC);
        BasicAI::scene->Delete(this, MOVING);
        BasicAI::scene->Add(new Explosion(x, y), STATIC);
        BasicAI::audio->Play(EXPLODE);
    }
}

// -------------------------------------------------------------------------------

void Blue::Update()
{
    // a magnitude do vetor 'target' controla quão 
    // rápido o objeto converge para a direção do alvo
    Vector target { Line::Angle(Point(x, y), Point(player->X(), player->Y())), 2.0f * gameTime };
    speed.Add(target);
    
    // limita a magnitude da velocidade para impedir 
    // que ela cresça indefinidamente pelo soma vetorial
    if (speed.Magnitude() > 4.5)
        speed.ScaleTo(4.5f);

    // move o objeto pelo seu vetor velocidade
    Translate(speed.XComponent() * 50.0f * gameTime, -speed.YComponent() * 50.0f * gameTime);

    // aplica fator de escala
    Scale(1.0f + factor * gameTime);

    // amplia e reduz objeto
    if (scale < 0.85f)
        factor = 0.25f;
    if (scale > 1.00f)
        factor = -0.25f;

    // mantém o objeto dentro do mundo do jogo
    if (x < 50)
        MoveTo(50, y);
    if (y < 50)
        MoveTo(x, 50);
    if (x > game->Width() - 50)
        MoveTo(game->Width() - 50, y);
    if (y > game->Height() - 50)
        MoveTo(x, game->Height() - 50);
}

// -------------------------------------------------------------------------------