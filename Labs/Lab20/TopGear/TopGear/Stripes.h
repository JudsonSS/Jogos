/**********************************************************************************
// Stripes (Arquivo de Cabeçalho)
//
// Criação:     11 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Faixas brancas da pista
//
**********************************************************************************/

#ifndef _TOPGEAR_STRIPES_H_
#define _TOPGEAR_STRIPES_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                             // objetos do jogo 
#include "Image.h"                              // carrega imagens
#include "Sprite.h"                             // desenho de sprites
#include "Types.h"                              // tipos específicos do motor

// ---------------------------------------------------------------------------------

class Stripes : public Object
{
private:
    Image * lines;                              // imagem das faixas brancas
    Sprite * sprite;                            // sprite das faixas brancas
    
    int first;                                  // índice da primeira faixa
    int last;                                   // índice da última faixa
    float pos[4] = {0};                         // posição das faixas
    float scale[4] = {0};                       // escala de desenho
    float delta[4] = {0};                       // valor do deslocamento
    float & speed;                              // velocidade do carro

public:
    Stripes();                                  // construtor
    ~Stripes();                                 // destrutor

    void Update();                              // atualização
    void Draw();                                // desenho
};

// ---------------------------------------------------------------------------------

#endif
