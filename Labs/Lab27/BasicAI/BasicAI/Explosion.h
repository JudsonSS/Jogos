/**********************************************************************************
// Explosion (Arquivo de Cabeçalho)
// 
// Criação:     17 Mar 2013
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#ifndef _BASICAI_EXPLOSION_H_
#define _BASICAI_EXPLOSION_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Particles.h"

// ---------------------------------------------------------------------------------

class Explosion : public Object
{
private:
    Particles * sparks;                 // sistema de partículas
    
public:
    Explosion(float pX, float pY);      // construtor
    ~Explosion();                       // destrutor

    int Size();                         // quantidade de partículas
    void Update();                      // atualização
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------

inline int Explosion::Size()
{ return sparks->Size(); }

inline void Explosion::Draw()
{ sparks->Draw(Layer::MIDDLE, 1.0f); }

// ---------------------------------------------------------------------------------


#endif