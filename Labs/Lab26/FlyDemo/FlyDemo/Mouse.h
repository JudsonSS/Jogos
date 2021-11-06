/**********************************************************************************
// Mouse (Arquivo de Cabeçalho)
// 
// Criação:     06 Ago 2019
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Gerencia mouse na tela
//
**********************************************************************************/

#ifndef _FLYDEMO_MOUSE_H_
#define _FLYDEMO_MOUSE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"        
#include "Types.h"        

// ---------------------------------------------------------------------------------

class Mouse : public Object
{
public:
    Mouse();                // construtor
    ~Mouse();               // destrutor

    void Update();          // atualização
    void Draw();            // desenho
}; 

// ---------------------------------------------------------------------------------

#endif