/**********************************************************************************
// Stage (Arquivo de Cabeçalho)
//
// Criação:     09 Ago 2019
// Atualização: 10 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria um estágio do jogo
//
**********************************************************************************/

#ifndef _PATTERNS_STAGE_H_
#define _PATTERNS_STAGE_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
#include "Random.h"
#include "Alien.h"

// --------------------------------------------------------------------------------

class Stage : public Object
{
private:
    Sprite * logo;              // logotipo do jogo
    Timer timer;                // medidor de tempo
    bool fase1;                 // fase 1 lançada
    bool fase2;                 // fase 2 lançada
    bool fase3;                 // fase 3 lançada
    bool fase4;                 // fase 4 lançada

    Alien * first[4];           // primeira onda de inimigos
    Alien * second[4];          // segunda onda de inimigos
    Alien * third[8];           // terceira onda de inimigos
    Alien * forth[8];           // quarta onda de inimigos
    Alien * fifth[8];           // quinta onda de inimigos
    Alien * sixth[8];           // sexta onda de inimigos

public:
    static uint enemies;        // quantidade de inimigos vivos

    Stage();                    // construtor
    ~Stage();                   // destrutor

    void Update();              // atualização
    void Draw();                // desenho
};

// ------------------------------------------------------------------------------

#endif
