/**********************************************************************************
// Lady (Arquivo de Cabeçalho)
//
// Criação:     27 Jan 2013
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto animado
//
**********************************************************************************/

#ifndef _ANIMAWALK_LADY_H_
#define _ANIMAWALK_LADY_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites

// ------------------------------------------------------------------------------

enum LadyState { STILL, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT };

// ---------------------------------------------------------------------------------

class Lady : public Object
{
private:
    TileSet   * walking;                // folha de sprites do personagem
    Animation * anim;                   // animação do personagem
    float       speed;                  // velocidade do personagem

public:
    uint state;                         // estado atual do personagem

    Lady();                             // construtor
    ~Lady();                            // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Lady::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif