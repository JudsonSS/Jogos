/**********************************************************************************
// Movable (Arquivo de Cabeçalho)
//
// Criação:     27 Jul 2019
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto movível através do mouse
//
**********************************************************************************/

#ifndef _COLLISIONT_MOVABLE_H_
#define _COLLISIONT_MOVABLE_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                              // tipos específicos da engine
#include "Object.h"                             // objetos do jogo
#include "Sprite.h"                             // desenho de sprites

// ---------------------------------------------------------------------------------

class Movable : public Object
{
protected:
    Sprite * sprite;                            // sprite do objeto
    bool colliding;                             // objeto em colisão
    bool following;                             // modo de perseguição do mouse
    float dx, dy;                               // distância para a posição do mouse

public:
    Movable();                                  // construtor
    virtual ~Movable();                         // destrutor

    virtual void OnCollision(Object* obj);      // resolução da colisão
    virtual void Update();                      // atualização
    virtual void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------

#endif
