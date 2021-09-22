/**********************************************************************************
// Ball (Arquivo de Cabeçalho)
//
// Criação:     28 Jun 2019
// Atualização: 22 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto Balão
//
**********************************************************************************/

#ifndef _BALLOONS_BALL_H_
#define _BALLOONS_BALL_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de um objeto
#include "Sprite.h"                                     // desenho de sprites
#include "TileSet.h"                                    // folha de sprites para a animação
#include "Animation.h"                                  // animação de sprites


// ---------------------------------------------------------------------------------

class Ball : public Object
{
private:
    Sprite * sprite;                                    // sprite do balão
    TileSet * tiles;                                    // quadros do estouro do balão
    Color color;                                        // cor do balão
    float vel;                                          // velocidade para subir

public:
    Ball(Image * img, TileSet * pop, Color tint);       // construtor
    ~Ball();                                            // destrutor

    void OnCollision(Object* obj);                      // resolução da colisão
    void Update();                                      // atualização do objeto
    void Draw();                                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Ball::Draw()
{ sprite->Draw(x, y, z, 1.0f, 0.0f, color); }

// ---------------------------------------------------------------------------------

#endif
