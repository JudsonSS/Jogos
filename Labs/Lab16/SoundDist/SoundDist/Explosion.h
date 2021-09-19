/**********************************************************************************
// Explosion (Arquivo de Cabeçalho)
// 
// Criação:     07 Fev 2013
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Animação de uma explosão
//
**********************************************************************************/

#ifndef _SOUNDDIST_EXPLOSION_H_
#define _SOUNDDIST_EXPLOSION_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites

// ---------------------------------------------------------------------------------

class Explosion : public Object
{
private:
    Animation * anim;                   // animação da explosão

public:
    Explosion(TileSet * tiles);         // construtor
    ~Explosion();                       // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Explosion::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif