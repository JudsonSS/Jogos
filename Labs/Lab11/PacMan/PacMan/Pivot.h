/**********************************************************************************
// Pivot (Arquivo de Cabeçalho)
// 
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Ponto de mudança de direção para o jogador e fantasmas
//
**********************************************************************************/

#ifndef _PACMAN_PIVOT_H_
#define _PACMAN_PIVOT_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                          // tipos específicos da engine
#include "Object.h"                         // interface de Object

// ---------------------------------------------------------------------------------

class Pivot : public Object
{
public:
    bool left  = false;                     // passagem livre a esquerda
    bool right = false;                     // passagem livre a direita
    bool up    = false;                     // passagem livre para cima
    bool down  = false;                     // passagem livre para baixo

    Pivot(bool l, bool r, bool u, bool d);  // construtor
    ~Pivot();                               // destrutor

    void Update() {};                       // atualização
    void Draw() {};                         // desenho
};

// ---------------------------------------------------------------------------------

#endif