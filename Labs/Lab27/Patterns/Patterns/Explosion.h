/**********************************************************************************
// Explosion (Arquivo de Cabeçalho)
//
// Criação:     10 Ago 2019
// Atualização: 10 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto representando uma explosão
//
**********************************************************************************/

#ifndef _PATTERNS_EXPLOSION_H_
#define _PATTERNS_EXPLOSION_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                         // objetos do jogo
#include "TileSet.h"                        // carregamento de imagens
#include "Animation.h"                      // desenho de sprites

// ---------------------------------------------------------------------------------

class Explosion : public Object
{
private:
    Animation * anim;                       // animação do objeto

public:
    Explosion(float posX, float posY);      // construtor
    ~Explosion();                           // destrutor

    void Update();                          // atualiza estado do objeto
    void Draw();                            // desenha objeto
};

// ---------------------------------------------------------------------------------

inline void Explosion::Draw()
{ anim->Draw(x, y); }

// ---------------------------------------------------------------------------------

#endif
