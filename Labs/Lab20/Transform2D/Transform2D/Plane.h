/**********************************************************************************
// Plane (Arquivo de Cabeçalho)
// 
// Criação:     24 Set 2012
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para um avião
//
**********************************************************************************/

#ifndef _TRANSFORM2D_PLANE_H_
#define _TRANSFORM2D_PLANE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"         // um avião é um objeto do jogo 
#include "Sprite.h"         // uma avião usa um sprite
#include "Types.h"          // tipos específicos do motor

// ---------------------------------------------------------------------------------

class Plane : public Object
{
private:
    Sprite * sprite;        // sprites do avião

public:
    Plane();                // construtor
    ~Plane();               // destrutor

    int Width();            // retorna largura do avião
    int Height();           // retorna altura do avião

    void Update();          // atualiza estado do avião
    void Draw();            // desenha avião
}; 

// ---------------------------------------------------------------------------------
// funções membro inline

inline int Plane::Width()
{ return sprite->Width(); }

// ---------------------------------------------------------------------------------

inline int Plane::Height()
{ return sprite->Height(); }

// ---------------------------------------------------------------------------------

#endif