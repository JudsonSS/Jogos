/**********************************************************************************
// Movable (Código Fonte)
//
// Criação:     27 Jul 2019
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto movível através do mouse
//
**********************************************************************************/

#include "CollisionT.h"
#include "Movable.h"

// ---------------------------------------------------------------------------------

Movable::Movable()
{
    sprite = nullptr;
    colliding = false;
    following = false;
    dx = dy = 0;
}

// ---------------------------------------------------------------------------------

Movable::~Movable()
{

}

// ---------------------------------------------------------------------------------

void Movable::OnCollision(Object * obj)
{
    if (obj->Type() != MOUSE)
    {
        // colisão com qualquer outro objeto
        colliding = true;
    }
    else
    {
        // colisão com o cursor do mouse
        if (window->KeyPress(VK_LBUTTON))
        {
            following = true;
            dx = x - window->MouseX();
            dy = y - window->MouseY();
            CollisionT::index = type;
        }
        if (window->KeyUp(VK_LBUTTON))
        {
            following = false;
        }
    }
}

// ---------------------------------------------------------------------------------

void Movable::Update()
{
    colliding = false;

    if (following)
    {
        MoveTo(window->MouseX() + dx, window->MouseY() + dy);
    }
}

// ---------------------------------------------------------------------------------

void Movable::Draw()
{
    if (colliding)
        sprite->Draw(x, y, z, scale, rotation, Color(1, 0, 0, 1)); // vermelho
    else
        sprite->Draw(x, y, z, scale, rotation, Color(1, 1, 1, 1)); // normal
}

// ---------------------------------------------------------------------------------