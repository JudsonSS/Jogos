/**********************************************************************************
// Pop (Arquivo de Cabeçalho)
// 
// Criação:     29 Jun 2019
// Atualização: 22 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Estouro do Balão
//
**********************************************************************************/

#ifndef _BALLOONS_POP_H_
#define _BALLOONS_POP_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "TileSet.h"                    // folha de sprites para a animação
#include "Animation.h"                  // animação de sprites

// ---------------------------------------------------------------------------------

class Pop : public Object
{
private:
    Animation * anim;                   // animação da explosão
    Color color;                        // cor do balão estourado

public:
    Pop(TileSet * tiles, Color tint);   // construtor
    ~Pop();                             // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Pop::Draw()
{ anim->Draw(x, y, z, color); }

// ---------------------------------------------------------------------------------

#endif