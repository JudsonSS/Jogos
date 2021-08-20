/**********************************************************************************
// Ball (Arquivo de Cabeçalho)
// 
// Criação:     22 Dez 2012
// Atualização: 20 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Bola do jogo Breakout
//
**********************************************************************************/

#ifndef _BREAKOUT_BALL_H_
#define _BREAKOUT_BALL_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Player.h"                     // jogador do Breakout

// ---------------------------------------------------------------------------------

class Ball : public Object
{
private:
    Player * player;                    // ponteiro para jogador
    Sprite * sprite;                    // sprite da bola

public:
    float velX;                         // velocidade horizontal
    float velY;                         // velocidade vertical    

    Ball(Player * p);                   // construtor
    ~Ball();                            // destrutor
    float Width();                      // largura da bola
    float Height();                     // altura da bola

    void OnCollision(Object * obj);     // tratamento de colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline float Ball::Width()
{ return float(sprite->Width()); }

inline float Ball::Height()
{ return float(sprite->Height()); }

inline void Ball::Draw()
{ sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif