/**********************************************************************************
// Mouse (Arquivo de Cabeçalho)
// 
// Criação:     27 Jul 2019
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Gerencia mouse na tela
//
**********************************************************************************/

#ifndef _COLLISIONT_MOUSE_H_
#define _COLLISIONT_MOUSE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"        
#include "Types.h"        

// ---------------------------------------------------------------------------------

class Mouse : public Object
{
public:
    Mouse();                            // construtor
    ~Mouse();                           // destrutor

    void OnCollision(Object* obj);      // resolução de colisão
    void Update();                      // atualização
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------

#endif