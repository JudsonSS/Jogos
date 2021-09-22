/**********************************************************************************
// Click (Arquivo de Cabeçalho)
//
// Criação:     29 Jun 2019
// Atualização: 22 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Click do Mouse
//
**********************************************************************************/

#ifndef _BALLOONS_CLICK_H_
#define _BALLOONS_CLICK_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "TileSet.h"                    // folha de sprites para a animação
#include "Animation.h"                  // animação de sprites

// ---------------------------------------------------------------------------------

class Click : public Object
{
private:
    Animation * anim;                   // animação do click

public:
    Click(TileSet * tiles);             // construtor
    ~Click();                           // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Click::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif