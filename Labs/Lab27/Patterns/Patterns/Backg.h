/**********************************************************************************
// Backg (Arquivo de Cabeçalho)
// 
// Criação:     21 Abr 2012
// Atualização: 10 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#ifndef _PATTERNS_BACKG_H_
#define _PATTERNS_BACKG_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // desenho de sprites

// ---------------------------------------------------------------------------------

class Backg : public Object
{
private:
    Sprite * backg;                     // pano de fundo

public:
    Backg();                            // construtor
    ~Backg();                           // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------

#endif