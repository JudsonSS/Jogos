/**********************************************************************************
// Obstacle (Arquivo de Cabeçalho)
// 
// Criação:     19 Dez 2012
// Atualização: 14 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Obstáculos do jogo Frogger
//
**********************************************************************************/

#ifndef _FROGGER_OBSTACLE_H_
#define _FROGGER_OBSTACLE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"            // tipos específicos da engine
#include "Object.h"           // interface de object
#include "Sprite.h"           // interface de sprites
#include "Image.h"            // interface de image

// ---------------------------------------------------------------------------------

class Obstacle : public Object
{
private:
    Sprite * sprite;
    float vel;

public:
    Obstacle(Image * img, float speed);
    ~Obstacle();

    void Update();
    void Draw();
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline

inline void Obstacle::Draw()
{ sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif