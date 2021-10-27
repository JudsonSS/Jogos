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
#include "TopGear.h"

// ---------------------------------------------------------------------------------

Cars::Cars() : deltaX(0), deltaY(0), speed(TopGear::speed)
{
    // carrega imagem do carro 
    img = new Image("Resources/WhiteCar.png");

    // cria sprite para o carro
    sprite = new Sprite(img);

    // cria bounding box
    BBox(new Rect(-65.0f, -26.0f,    65.0f, 0.0f));

    // posição inicial do carro
    lane = randPos(mt);
    MoveTo(positions[lane], 246);

    // ajusta a escala inicial
    ScaleTo(0.1f);
}

// ---------------------------------------------------------------------------------

Cars::~Cars()
{
    delete img;
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Cars::MoveUp(float val)
{
    switch (lane)
    {
    case 0: Translate(val, -1 * val); break;
    case 1: Translate(0, -1 * val); break;
    case 2: Translate(-1 * val, -1 * val); break;
    }
}

// ---------------------------------------------------------------------------------

void Cars::Update()
{    
    // deslocamento varia com a escala e a velocidade do player
    deltaY = speed/10.0f * scale * gameTime;

    // deslocamento horizontal é igual ao deslocamento vertical
    // <-- 447 para 221 = 226 pixels no X ao longo de 227 no Y
    // --> 511 para 738 = 227 pixels no X ao longo de 227 no Y
    switch (lane)
    {
    case 0: deltaX = -deltaY; break;
    case 1: deltaX = 0; break;
    case 2: deltaX = deltaY; break;
    }

    // desloca carro
    Translate(deltaX, deltaY);

    // o carro vai percorrer 227 pixels até chegar a posição de escala igual a 1.0
    // como ele inicia na escala 0.1, sua escala deve variar de 0.9 em 227 pixels, 
    // ou seja, aumento de 0.9/227 = 0.00396475 por pixel
    
    // aumenta a escala de acordo com a distância percorrida
    ScaleTo(scale + deltaY * 0.00396475f);
    
    // verifica a distância do carro para o início da pista
    if (y - 246 >= 500)
    {
        // restaura posição e escala do início da pista
        ScaleTo(0.1f);
        lane = randPos(mt);
        MoveTo(positions[lane], 246);
    }
}

// -------------------------------------------------------------------------------

void Cars::Draw()
{
    // desenha carro usando a escala definida
    sprite->Draw(x, y, Layer::UPPER, scale);
}

// -------------------------------------------------------------------------------