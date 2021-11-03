/**********************************************************************************
// Orange (Arquivo de Cabeçalho)
// 
// Criação:     05 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz movimento retilíneo
//
**********************************************************************************/

#ifndef _GEOWARS_ORANGE_H_
#define _GEOWARS_ORANGE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

class Orange : public Object
{
private:
    Sprite * sprite;                    // sprite do objeto
    Vector * speed;                     // velocidade e direção
    Player * player;                    // ponteiro para jogador
    Particles * tail;                   // calda da nave laranja
    float multiplier;                   // multiplicador da velocidade
    
public:
    Orange(Player * p);                 // construtor
    ~Orange();                          // destrutor
    
    void OnCollision(Object* obj);      // resolução da colisão
    void Update();                      // atualização
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------


#endif