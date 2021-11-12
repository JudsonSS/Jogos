/**********************************************************************************
// Blue (Arquivo de Cabeçalho)
// 
// Criação:     10 Out 2012
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz uma perseguição suavizada
//
**********************************************************************************/

#ifndef _BASICAI_BLUE_H_
#define _BASICAI_BLUE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

class Blue : public Object
{
private:
    Sprite * sprite;                            // sprite do objeto
    Player * player;                            // ponteiro para jogador
    Vector speed;                               // velocidade e direção
    float factor;                               // fator de escala
    
public:
    Blue(float pX, float pY, Player * p);       // construtor
    ~Blue();                                    // destrutor
    
    void OnCollision(Object* obj);              // resolução da colisão
    void Update();                              // atualização
    void Draw();                                // desenho
}; 

// ---------------------------------------------------------------------------------

inline void Blue::Draw()
{ sprite->Draw(x, y, Layer::LOWER, scale, rotation); }

// ---------------------------------------------------------------------------------


#endif