/**********************************************************************************
// Stripes (Código Fonte)
//
// Criação:     11 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Faixas brancas da pista
//
**********************************************************************************/

#include "Stripes.h"
#include "TopGear.h"
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

Stripes::Stripes() : speed(TopGear::speed)
{
    // carrega imagem das faixas
    lines = new Image("Resources/Stripes.png");

    // cria sprite para as faixas
    sprite = new Sprite(lines);

    // posições iniciais das faixas
    pos[0] = 250.0f;  // 0
    pos[1] = 280.0f;  // 30 
    pos[2] = 340.0f;  // 60 
    pos[3] = 460.0f;  // 120

    // índice da primeira e última faixa
    first = 0;
    last = 3;

    // Ao longo de 340 pixels (290 da altura da pista + 4 antes + 46 depois da pista)
    // a escala deve ir de 1.0 até 0.074889. Esse valor foi obtido a partir
    // do cálculo abaixo, que usa a largura das linhas no final da pista (454 pixels), 
    // e a largura delas no inicio da pista (34 pixels):
    // 
    //   454 * escala = 34, ou seja, escala = 0.074889
    // 
    // Então a variação da escala será de 0.925110 em 340 pixels. Isso implica em um 
    // acréscimo de 0.00272091 no valor da escala a cada pixel do eixo Y:
    //
    //    1.0 - 0.074889 = 0.925110
    //    0.925110/340 = 0.00272091
    //
    // Dada uma posição "pos" de início do desenho, podemos encontrar a escala
    // correta para esse desenho multiplicando a distância já percorrida (em 
    // relação a posição máxima do eixo Y) por 0.00272091 e tirando esse resultado
    // da escala original (1.0f)

    // ajusta a escala conforme a posição inicial
    for (int i = 0; i < 4; ++i)
        scale[i] = 1.0f - (586.0f - pos[i]) * 0.00272091f;
}

// ---------------------------------------------------------------------------------

Stripes::~Stripes()
{
    delete sprite;
    delete lines;
}

// ---------------------------------------------------------------------------------

void Stripes::Update()
{
    for (int i = 0; i < 4; ++i)
    {
        // deslocamento varia com a escala e a velocidade do carro
        delta[i] = 1.2f * speed * scale[i] * gameTime;

        // desloca faixas
        pos[i] += delta[i];

        // aumenta a escala de acordo com a distância percorrida
        scale[i] += delta[i] * 0.00272091f;
    }

    // verifica a distância da primeira faixa para o início da pista
    if (pos[first] - 246.5 >= 30)
    {
        // restaura escala da última faixa para o início da pista
        scale[last] = 0.074889f;

        // posiciona última faixa no início da pista
        pos[last] = 250.0f - (sprite->Height() * scale[last] / 2.0f);

        // a última faixa se tornou a primeira e agora existe uma nova última
        first = last--;

        // trata vetor de forma circular
        if (last < 0)
            last = 3;
    }
}

// -------------------------------------------------------------------------------

void Stripes::Draw()
{
    // desenha linhas usando a escala definida
    for (int i = 0; i < 4; ++i)
        sprite->Draw(window->CenterX(), pos[i], Layer::MIDDLE, scale[i]);
}

// -------------------------------------------------------------------------------