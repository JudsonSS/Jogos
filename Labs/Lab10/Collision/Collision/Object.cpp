/**********************************************************************************
// Object (Código Fonte)
//
// Criação:     01 Out 2007
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Essa é a classe base para todos objetos do jogo.
//
//              Um objeto do jogo é qualquer coisa que possámos querer desenhar
//              ou interagir dentro do jogo. Por exemplo, um soldado, um prédio,
//              um projétil, uma forma geométrica, etc.
//
**********************************************************************************/

#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

Window* & Object::window   = Engine::window;        // ponteiro para a janela
Game*   & Object::game     = Engine::game;          // ponteiro para o jogo
float   & Object::gameTime = Engine::frameTime;     // tempo do último quadro

// -------------------------------------------------------------------------------

Object::Object()
{
    // posição do objeto
    posX = posY = 0.0f;

    // profundidade do objeto
    posZ = 0.5f;

    //tipo do objeto
    type = 0;

    // bounding box do objeto
    bbox = nullptr;
}

// -------------------------------------------------------------------------------

Object::~Object()
{
    if (bbox)
        delete bbox;
}

// -------------------------------------------------------------------------------

void Object::BBox(Geometry* bb)
{
    if (bbox)
        delete bbox;

    bbox = bb;
    bbox->Translate(x, y);
}

// -------------------------------------------------------------------------------

void Object::Translate(float dx, float dy, float dz)
{
    posX += dx;
    posY += dy;
    posZ += dz;

    if (bbox)
        bbox->Translate(dx, dy);
}

// -------------------------------------------------------------------------------

void Object::MoveTo(float px, float py, float pz)
{
    posX = px;
    posY = py;
    posZ = pz;

    if (bbox)
        bbox->MoveTo(px, py);
}

// -------------------------------------------------------------------------------

void Object::MoveTo(float px, float py)
{
    posX = px;
    posY = py;

    if (bbox)
        bbox->MoveTo(px, py);
}

// -------------------------------------------------------------------------------

void Object::OnCollision(Object* obj)
{
}

// -------------------------------------------------------------------------------