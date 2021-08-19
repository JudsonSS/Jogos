/**********************************************************************************
// Alien (Arquivo de Cabeçalho)
// 
// Criação:     21 Dez 2012
// Atualização: 18 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Alienígena do jogo Galaga
//
**********************************************************************************/

#include "Alien.h"

// ---------------------------------------------------------------------------------

Alien::Alien(string filename)
{
    sprite = new Sprite(filename);
    vel = 80.0f;
}

// ---------------------------------------------------------------------------------

Alien::~Alien()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Alien::Update()
{
    // desloca alien
    x += vel * gameTime;

    // mantêm os alienígenas dentro da janela
    // tamanho das imagens é 28x30

    // alien saindo pela esquerda
    if (x + sprite->Width() < 0)
        x = float(window->Width());

    // alien saindo pela direita
    if (x > window->Width())
        x = float(-sprite->Width());
}

// ---------------------------------------------------------------------------------
