/**********************************************************************************
// Missile (Arquivo de Cabeçalho)
// 
// Criação:     21 Dez 2012
// Atualização: 18 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Mísseis do jogo Galaga
//
**********************************************************************************/

#ifndef _GALAGA_MISSILE_H_
#define _GALAGA_MISSILE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"              // tipos específicos da engine
#include "Object.h"             // interface de object
#include "Sprite.h"             // interface de sprites
#include "Image.h"              // interface de image

// ---------------------------------------------------------------------------------

class Missile : public Object
{
private:
    Sprite * sprite;
    float vel;

public:
    Missile(Image * img);
    ~Missile();

    void Update();
    void Draw();
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline
inline void Missile::Draw()
{  sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif