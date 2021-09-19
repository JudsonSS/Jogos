/**********************************************************************************
// Platform (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType)
{
    // seleciona tipo de plataforma
    switch (platType)
    {
    case SMALL:  platform = new Sprite("Resources/SmallGray.png"); break;
    case MEDIUM: platform = new Sprite("Resources/MediumGray.png"); break;
    case LARGE:  platform = new Sprite("Resources/LongGray.png"); break;
    }
    
    // cria bounding box
    BBox(new Rect(-1.0f * platform->Width()/2.0f, 
                  -1.0f * platform->Height()/2.0f, 
                  platform->Width()/2.0f,        
                  platform->Height()/2.0f));

    // posição inicial da plataforma
    MoveTo(posX, posY, Layer::UPPER);
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
    // move plataforma
    Translate(-200.0f * gameTime, 0);
}

// -------------------------------------------------------------------------------
