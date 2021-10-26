/**********************************************************************************
// Shapes (Código Fonte)
//
// Criação:     27 Jul 2019
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objetos de diferentes formas
//
**********************************************************************************/

#include "CollisionT.h"
#include "Shapes.h"

// ---------------------------------------------------------------------------------

Box::Box()
{
    sprite = new Sprite("Resources/Box.png");
    BBox(new Rect(-50, -50, 50, 50));
    MoveTo(226, 180);
    type = BOX;
}

Box::~Box()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

Wheel::Wheel()
{
    sprite = new Sprite("Resources/Wheel.png");
    BBox(new Circle(50));
    MoveTo(426, 180);
    type = WHEEL;
}

Wheel::~Wheel()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

Drop::Drop()
{
    sprite = new Sprite("Resources/Drop.png");
    BBox(new Point());
    MoveTo(576, 180);
    type = DROP;
}

Drop::~Drop()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

Plane::Plane()
{
    sprite = new Sprite("Resources/Plane.png");

    Point vertex[18] =
    {
        Point(-10,-41), Point(-4,-46), Point(4,-46), Point(10,-41), 
        Point(10,-22), Point(65,-20), Point(65,-13), Point(7,6), 
        Point(2,36), Point(18,41), Point(18,47), Point(-17,47), Point(-17,41), Point(-2,36), 
        Point(-7,6), Point(-65,-13), Point(-65,-20), Point(-10,-22)
    };

    BBox(new Poly(vertex, 18));
    MoveTo(726, 180);
    type = PLANE;
}

Plane::~Plane()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

Hammer::Hammer()
{
    sprite = new Sprite("Resources/Hammer.png");
    
    Mixed* mixed = new Mixed();
    mixed->Insert(new Rect(-28, -48, 26, -23));
    mixed->Insert(new Rect(-6, -50, 5, 48));

    BBox(mixed);    
    MoveTo(926, 180);
    type = HAMMER;
}

Hammer::~Hammer()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

Display::Display()
{
    sprite = new Sprite("Resources/Display.png");
    BBox(new Rect(-47, -49, 46, 49));
    MoveTo(226, 380);
    type = DISPLAY;
}

Display::~Display()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

Ball::Ball()
{
    sprite = new Sprite("Resources/Ball.png");
    BBox(new Circle(49));
    MoveTo(426, 380);
    type = BALL;
}

Ball::~Ball()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

Dot::Dot()
{
    sprite = new Sprite("Resources/Dot.png");
    BBox(new Point());
    MoveTo(576, 380);
    type = DOT;
}

Dot::~Dot()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

Bolt::Bolt()
{
    sprite = new Sprite("Resources/Bolt.png");
    BBox(new Rect(-29, -42, 35, 48));
    MoveTo(726, 380);
    type = BOLT;
}

Bolt::~Bolt()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

House::House()
{
    sprite = new Sprite("Resources/House.png");
    Point vertex[3] = { Point(-50,-4), Point(0,-42), Point(49,-4) };

    Mixed * mixed = new Mixed();
    mixed->Insert(new Rect(-42, -4, 41, 40));
    mixed->Insert(new Rect(20, -40, 32, -4));
    mixed->Insert(new Poly(vertex, 3));

    BBox(mixed);
    MoveTo(926, 380);
    type = HOUSE;
}

House::~House()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------