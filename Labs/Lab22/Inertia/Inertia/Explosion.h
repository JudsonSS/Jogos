/**********************************************************************************
// Explosion (Arquivo de Cabeçalho)
// 
// Criação:     07 Fev 2013
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Animação de uma explosão
//
**********************************************************************************/

#ifndef _INERTIA_EXPLOSION_H_
#define _INERTIA_EXPLOSION_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // objetos do jogo
#include "Animation.h"                  // animação de sprites

// ---------------------------------------------------------------------------------

class Explosion : public Object
{
private:
    Animation * anim;                   // animação

public:
    Explosion(TileSet * tiles);         // construtor
    ~Explosion();                       // destrutor

    void Update();                      // atualização
    void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Explosion::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif