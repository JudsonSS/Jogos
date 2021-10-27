/**********************************************************************************
// Cars (Arquivo de Cabeçalho)
//
// Criação:     14 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Carros adversários
//
**********************************************************************************/

#ifndef _TOPGEAR_CARS_H_
#define _TOPGEAR_CARS_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                             // objetos do jogo 
#include "Image.h"                              // uso de imagens
#include "Sprite.h"                             // desenho de sprites
#include "Types.h"                              // tipos específicos do motor
#include <random>                               // gerador de números aleatórios

// ---------------------------------------------------------------------------------

using std::uniform_int_distribution;
using std::random_device;
using std::mt19937;
using DistInt = uniform_int_distribution<int>;

// ---------------------------------------------------------------------------------

class Cars : public Object
{
private:
    Image * img;                                // imagem do carro branco
    Sprite * sprite;                            // sprite do carro branco

    float deltaX;                               // valor do deslocamento eixo X
    float deltaY;                               // valor do deslocamento eixo Y
    float& speed;                               // velocidade do carro

    random_device rd;                           // gerador não-determinístico
    mt19937 mt{rd()};                           // gerador mersenne twister
    DistInt randPos{ 0, 2 };                    // distribui aleatóriamente

    float positions[3] = { 447, 480, 511 };     // posições iniciais no eixo X
    int lane;                                   // número da faixa da pista em uso

public:
    Cars();                                     // construtor
    ~Cars();                                    // destrutor

    void MoveUp(float val);                     // move o carro em uma colisão
    void Update();                              // atualiza estado do avião
    void Draw();                                // desenha avião
};

// ---------------------------------------------------------------------------------

#endif

