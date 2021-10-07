/**********************************************************************************
// Cars (Código Fonte)
//
// Criação:     14 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Carros adversários
//
**********************************************************************************/

#include "Cars.h"

// ---------------------------------------------------------------------------------

Cars::Cars() 
{
    // cria sprite para o carro
    sprite = new Sprite("Resources/WhiteCar.png");

    // deslocamentos no eixo X e Y
    deltaX = 0;
    deltaY = 0;

    // velocidade inicial do carro
    speed = 100;

    // --- ajuste a posição inicial do carro ---

    // --- ajuste a escala inicial do carro ---
}

// ---------------------------------------------------------------------------------

Cars::~Cars()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Cars::Update()
{
    // deslocamento varia com a escala e a velocidade
    deltaY = speed * scale * gameTime;

    // desloca carro
    Translate(deltaX, deltaY);

    // --- aumente a escala de acordo com a distância percorrida ---
    
    
    // verifica a distância do carro para o início da pista
    if (y - 246 >= 500)
    {
        // restaura posição e escala do início da pista
        ScaleTo(0.1f);
        MoveTo(window->CenterX(), 246);
    }
}

// -------------------------------------------------------------------------------

void Cars::Draw()
{
    // --- desenha carro usando a escala definida ---

}

// -------------------------------------------------------------------------------