/**********************************************************************************
// Magenta (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz um perseguição direta
//
**********************************************************************************/

#include "ChaseDemo.h"
#include "Magenta.h"
#include "Random.h" 
#include "Hud.h"

// ---------------------------------------------------------------------------------

Magenta::Magenta(float pX, float pY, Player * p)
{
    player = p;
    sprite = new Sprite("Resources/Magenta.png");
    BBox(new Circle(18.0f));
    
    speed.RotateTo(0);
    speed.ScaleTo(2.0f);
    
    MoveTo(pX, pY);
    type = MAGENTA;

    // incrementa contador
    ++Hud::enemies;
}

// ---------------------------------------------------------------------------------

Magenta::~Magenta()
{
    delete sprite;

    // decrementa contador
    --Hud::enemies;
}

// -------------------------------------------------------------------------------

void Magenta::OnCollision(Object * obj)
{
    if (obj->Type() == MISSILE)
    {
        ChaseDemo::scene->Delete(obj, STATIC);
        ChaseDemo::scene->Delete(this, MOVING);
        ChaseDemo::audio->Play(EXPLODE);
    }
}

// -------------------------------------------------------------------------------

void Magenta::Update()
{
    // ajusta ângulo do vetor 
    speed.RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    Rotate(200 * gameTime);

    // movimenta objeto pelo seu vetor velocidade
    Translate(speed.XComponent() * 50.0f * gameTime, -speed.YComponent() * 50.0f * gameTime);
}

// -------------------------------------------------------------------------------