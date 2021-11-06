/**********************************************************************************
// Fly (Arquivo de Cabeçalho)
// 
// Criação:     10 Out 2012
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Simula o vôo aleatório de uma mosca
//
**********************************************************************************/

#ifndef _FLYDEMO_FLY_H_
#define _FLYDEMO_FLY_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Timer.h"
#include "Random.h"

// ---------------------------------------------------------------------------------

class Fly : public Object
{
private:
    Sprite * sprite;                // sprite da mosca
    Vector speed;                   // velocidade e direção
    Timer timer;                    // medidor do tempo de vôo
    RandF magnitude;                // valor de magnitude aleatória
    RandF angle;                    // valor de ângulo aleatório    
    RandF secs;                     // valor de segundos aleatório
    float delay;                    // tempo para mudança de direção
    
public:
    Fly(Image * img);               // construtor    
    ~Fly();                         // destrutor
    
    void NewDirection();            // muda direção da mosca
    void Update();                  // atualização
    void Draw();                    // desenho
}; 

// ---------------------------------------------------------------------------------

inline void Fly::Draw()
{ sprite->Draw(x, y, Layer::UPPER, scale); }

// ---------------------------------------------------------------------------------


#endif