/**********************************************************************************
// WallHit (Arquivo de Cabeçalho)
// 
// Criação:     03 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#ifndef _BASICAI_WALLHIT_H_
#define _BASICAI_WALLHIT_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Particles.h"
#include "Missile.h"

// ---------------------------------------------------------------------------------

class WallHit : public Object
{
private:
    Particles * sparks;                 // sistema de partículas
    
public:
    WallHit(float pX, float pY);        // construtor
    ~WallHit();                         // destrutor

    int  Size();                        // quantidade de partículas
    void Update();                      // atualização
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------

inline int WallHit::Size()
{ return sparks->Size(); }

inline void WallHit::Draw()
{ sparks->Draw(Layer::MIDDLE, 0.0f); }

// ---------------------------------------------------------------------------------


#endif