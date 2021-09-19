/**********************************************************************************
// Missile (Arquivo de Cabeçalho)
// 
// Criação:     07 Fev 2013
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Mísseis usados em SoundDist
//
**********************************************************************************/

#ifndef _SOUNDDIST_MISSILE_H_
#define _SOUNDDIST_MISSILE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                                  // tipos específicos da engine
#include "Object.h"                                 // interface de object
#include "Sprite.h"                                 // interface de sprites
#include "Image.h"                                  // interface de image
#include "TileSet.h"                                // interface de tileset

// ---------------------------------------------------------------------------------

class Missile : public Object
{
private:
    TileSet * explodSet;                            // folha de sprites da explosão                
    Sprite * sprite;                                // sprite do míssil
    float vel;                                      // velocidade do míssil

public:
    Missile(Image * img, TileSet * explosion);      // construtor
    ~Missile();                                     // destrutor

    void OnCollision(Object * obj);                 // resolução da colisão
    void Update();                                  // atualização do objeto
    void Draw();                                    // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline
inline void Missile::Draw()
{  sprite->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif