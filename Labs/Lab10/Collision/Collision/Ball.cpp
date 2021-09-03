/**********************************************************************************
// Ball (Arquivo de Cabeçalho)
// 
// Criação:     22 Dez 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Bola do jogo Breakout
//
**********************************************************************************/

#include "Ball.h"
#include "Block.h"
#include "Breakout.h"

// ---------------------------------------------------------------------------------

Ball::Ball(Player * p)
{
    // guarda jogador
    player = p;

    // tamanho da bola é 12x12
    BBox(new Rect(0, 0, 11, 11));
    
    // bounding box alternativa: experimente  
    // usar o círculo no lugar do retângulo
    //bbox = new Circle(6);

    // cria sprite da bola
    sprite  = new Sprite("Resources/Ball.png");

    // tamanho do player é 100x20
    MoveTo(player->X() + 50.0f - sprite->Width()/2.0f, 
           player->Y() - sprite->Height() - 2.0f, 
           Layer::FRONT);

    // velocidades iniciais
    velX = 300.0f;
    velY = -300.0f;

    // tipo do objeto
    type = BALL;
}

// ---------------------------------------------------------------------------------

Ball::~Ball()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Ball::OnCollision(Object * obj)
{
    // bola colide com bloco
    if (obj->Type() == BLOCK)
        Breakout::scene->Delete(obj, STATIC);

    // experimente deixar o bloco cair em vez de removê-lo da cena
        //((Block*) obj)->velY = 200.0f;
}

// ---------------------------------------------------------------------------------

void Ball::Update()
{
    if (player->state == PLAYING)
    {
        Translate(velX * gameTime, velY * gameTime);

        // se o jogador não rebater, a bola é reiniciada
        //if (y + sprite->Height() > window->Height())
        //    player->state = STOPED;
    }
    else
    {
        // mova para posição acima do player e o acompanhe
        MoveTo(player->X() + 50.0f - sprite->Width() / 2.0f, player->Y() - sprite->Height() - 2.0f, Layer::FRONT);
    }
        

    // mantém a bola dentro da tela (tam. da bola: 12x12)
    if (x < 0)
    {
        MoveTo(0.0f, y);
        velX = -velX;
    }
    if (x + sprite->Width() > window->Width())
    {
        MoveTo(float(window->Width() - sprite->Width()), y);
        velX = -velX;
    }
    if (y < 0)
    {
        MoveTo(x, 0.0f);
        velY = -velY;
    }
    if (y + sprite->Height() > window->Height())
    {
        MoveTo(x, float(window->Height() - sprite->Height()));
        velY = -velY;
    }
}

// ---------------------------------------------------------------------------------
