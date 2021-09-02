/**********************************************************************************
// Lady (Código Fonte)
//
// Criação:     27 Jan 2013
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Objeto animado
//
**********************************************************************************/

#include "Lady.h"

// ---------------------------------------------------------------------------------

Lady::Lady()
{
    walking = new TileSet("Resources/Walking.png", 55, 95, 8, 40);
    anim    = new Animation(walking, 0.060f, true);

    uint SeqUp[8]    = { 16, 17, 18, 19, 20, 21, 22, 23 };
    uint SeqDown[8]  = { 24, 25, 26, 27, 28, 29, 30, 31 };
    uint SeqLeft[8]  = { 0, 1, 2, 3, 4, 5, 6, 7 };
    uint SeqRight[8] = { 15, 14, 13, 12, 11, 10, 9, 8 };
    uint SeqStill[1] = { 32 };

    anim->Add(WALKUP,    SeqUp,    8);
    anim->Add(WALKDOWN,  SeqDown,  8);
    anim->Add(WALKLEFT,  SeqLeft,  8);
    anim->Add(WALKRIGHT, SeqRight, 8);
    anim->Add(STILL,     SeqStill, 1);

    state = STILL;
    speed = 300.0f;
    MoveTo(window->CenterX(), window->CenterY());
}

// ---------------------------------------------------------------------------------

Lady::~Lady()
{
    delete anim;
    delete walking;
}

// ---------------------------------------------------------------------------------

void Lady::Update()
{
    // anda para cima
    if (window->KeyDown(VK_UP))
    {
        Translate(0, -speed * gameTime);
        state = WALKUP;
    }

    // anda para baixo
    if (window->KeyDown(VK_DOWN))
    {
        state = WALKDOWN;
        Translate(0, speed * gameTime);
    }

    // anda para esquerda
    if (window->KeyDown(VK_LEFT))
    {
        state = WALKLEFT;
        Translate(-speed * gameTime, 0);
    }

    // anda para direita
    if (window->KeyDown(VK_RIGHT))
    {
        state = WALKRIGHT;
        Translate(speed * gameTime, 0);
    }

    // se todas as teclas estão liberadas, mude para o estado parado
    if (window->KeyUp(VK_UP) && window->KeyUp(VK_DOWN) && window->KeyUp(VK_LEFT) && window->KeyUp(VK_RIGHT))
    {
        state = STILL;
    }

    // atualiza animação
    anim->Select(state);
    anim->NextFrame();

    // mantém personagem dentro da tela
    if (x + walking->TileWidth() / 2.0f > window->Width())
        MoveTo(window->Width() - walking->TileWidth() / 2.0f, y);

    if (x - walking->TileWidth() / 2.0f < 0)
        MoveTo(walking->TileWidth() / 2.0f, y);

    if (y + walking->TileHeight() / 2.0f > window->Height())
        MoveTo(x, window->Height() - walking->TileHeight() / 2.0f);

    if (y - walking->TileHeight() / 2.0f < 0)
        MoveTo(x, walking->TileHeight() / 2.0f);
}

// ---------------------------------------------------------------------------------