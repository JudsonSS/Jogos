/**********************************************************************************
// Animation (Código Fonte)
// 
// Criação:     28 Set 2011
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Classe para animar sequências em folha de sprites
//
**********************************************************************************/

#include "Engine.h"
#include "Animation.h"
#include "Renderer.h"

// ---------------------------------------------------------------------------------

Animation::Animation(TileSet * tiles, float delay, bool repeat) : 
    tileSet(tiles), 
    animDelay(delay), 
    animLoop(repeat)
{
    // sempre inicia a animação pelo primeiro quadro
    frame = iniFrame = 0;

    // o último quadro é sempre um a menos que o número de quadros
    endFrame = tileSet->Size() - 1;

    // configura sprite
    sprite.width     = tileSet->TileWidth();
    sprite.height    = tileSet->TileHeight();
    sprite.texSize.x = float(tileSet->TileWidth())  / tileSet->Width();
    sprite.texSize.y = float(tileSet->TileHeight()) / tileSet->Height();
    sprite.texture   = tileSet->View();
    
    // animação iniciada (começa a contar o tempo)
    timer.Start();                

    // nenhuma sequência selecionada
    sequence = nullptr;
}

// --------------------------------------------------------------------------------

Animation::~Animation()
{
    if (!table.empty())
    {
        // liberando memória dos vetores dinâmicos de sequências
        for (const auto & [id,seq] : table)
            delete seq.first;
    }
}

// --------------------------------------------------------------------------------

void Animation::Add(uint id, uint * seq, uint seqSize)
{
    // cria nova sequência de animação
    AnimSeq newSeq(new uint[seqSize], seqSize);

    // copia vetor com a sequência de quadros
    memcpy(newSeq.first, seq, sizeof(uint) * seqSize);

    // insere nova sequência
    table[id] = newSeq;

    // seleciona sequência recém inserida
    sequence = newSeq.first;

    // inicia animação pelo primeiro quadro da sequência
    iniFrame = frame = 0;

    // o último quadro é sempre um a menos que o número de quadros
    endFrame = seqSize - 1;
}

// --------------------------------------------------------------------------------

void Animation::Select(uint id)
{
    const auto & [seq, size] = table[id];

    // se uma nova sequência for selecionada
    if (sequence != seq)
    {
        // aponta para nova sequência
        sequence = seq;

        // reinicia a sequência
        iniFrame = 0;
        endFrame = size - 1;

        // se o frame atual está fora da sequência
        if (frame > endFrame)
            frame = 0;
    }
}


// ---------------------------------------------------------------------------------

void Animation::NextFrame()
{
    // passa para o próximo quadro após espaço de tempo estipulado em animDelay
    if (timer.Elapsed(animDelay))
    {
        frame++;

        // se chegou ao fim da animação
        if (frame > endFrame)
        {
            // se a animação estiver em loop
            if (animLoop)
            {
                // volta ao primeiro quadro 
                frame = 0;
                timer.Start();
            }
            else
            {
                // fica no último quadro
                frame = endFrame;
            }
        }
        else
        {
            // começa a contar o tempo do novo frame
            timer.Start();
        }
    }
}

// ---------------------------------------------------------------------------------

void Animation::Draw(uint aFrame, float x, float y, float z, float scale, float rotation, Color color)
{
    // ajusta coordenadas usando a viewport
    x -= Engine::game->viewport.left;
    y -= Engine::game->viewport.top;

    // configura dados básicos
    sprite.x = x;
    sprite.y = y;
    sprite.depth = z;
    sprite.scale = scale;
    sprite.rotation = rotation * XM_PI / 180.0f;
    sprite.color = color;

    // configura coordenadas da textura do sprite
    sprite.texCoord.x = (aFrame % tileSet->Columns()) * sprite.texSize.x;
    sprite.texCoord.y = (aFrame / tileSet->Columns()) * sprite.texSize.y;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(sprite);
}

// --------------------------------------------------------------------------------