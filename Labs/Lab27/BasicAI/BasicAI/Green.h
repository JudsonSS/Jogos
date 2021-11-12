/**********************************************************************************
// Green (Arquivo de Cabeçalho)
// 
// Criação:     15 Out 2012
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto faz uma fuga suavizada
//
**********************************************************************************/

#ifndef _BASICAI_GREEN_H_
#define _BASICAI_GREEN_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

class Green : public Object
{
private:
    Sprite * sprite;                            // sprite do objeto
    Player * player;                            // ponteiro para jogador
    Vector speed;                               // velocidade e direção
    int distance;                               // distância do jogador
    
public:
    Green(float pX, float pY, Player * p);      // construtor
    ~Green();                                   // destrutor
    
    void OnCollision(Object* obj);              // resolução da colisão
    void Update();                              // atualização
    void Draw();                                // desenho
}; 

// ---------------------------------------------------------------------------------

inline void Green::Draw()
{ sprite->Draw(x, y, Layer::LOWER, scale, rotation); }

// ---------------------------------------------------------------------------------


#endif