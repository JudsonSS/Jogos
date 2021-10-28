/**********************************************************************************
// Smoke (Arquivo de Cabeçalho)
// 
// Criação:     17 Mar 2013
// Atualização: 27 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Efeito de fumaça usando sistema de partículas
//
**********************************************************************************/

#ifndef _REFINERY_SMOKE_H_
#define _REFINERY_SMOKE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Particles.h"
#include "Types.h"

// ---------------------------------------------------------------------------------

class Smoke : public Object
{
private:
    Particles * smokeGen;               // sistema de partículas
    bool stop;                          // estado da geração de fumaça
    
public:
    Smoke(float pX, float pY,           // posição x, y
          float angle,                  // ângulo da fumaça
          bool night);                  // dia ou noite
    
    ~Smoke();                           // destrutor

    int  Size();                        // quantidade de partículas
    void TurnOff();                     // desligar fumaça

    void Update();                      // atualização
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------

inline int Smoke::Size()
{ return smokeGen->Size(); }

inline void Smoke::Draw()
{ smokeGen->Draw(Layer::MIDDLE, 1.0f); }

// ---------------------------------------------------------------------------------


#endif