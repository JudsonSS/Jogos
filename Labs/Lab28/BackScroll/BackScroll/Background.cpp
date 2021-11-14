/**********************************************************************************
// Background (Código Fonte)
// 
// Criação:     07 Dez 2011
// Atualização: 12 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Representa um pano de fundo maior que a janela
//
**********************************************************************************/


#include "Background.h"
#include "Engine.h"

// -------------------------------------------------------------------------------

Background::Background(string filename)
{
    // carrega imagem
    image = new Image(filename);
    localImage = true;

    // configura registro spriteData
    spriteData.x = Engine::window->CenterX();
    spriteData.y = Engine::window->CenterY();
    spriteData.depth = Layer::BACK;
    spriteData.scale = 1.0f;    
    spriteData.rotation = 0.0f;
    spriteData.color = Color(1, 1, 1, 1);
    spriteData.texture = image->View();
}

// -------------------------------------------------------------------------------

Background::Background(const Image* img)
{
    // aponta para imagem
    image = img;
    localImage = false;

    // configura registro spriteData
    spriteData.x = Engine::window->CenterX();
    spriteData.y = Engine::window->CenterY();
    spriteData.depth = Layer::BACK;
    spriteData.scale = 1.0f;
    spriteData.rotation = 0.0f;
    spriteData.color = Color(1, 1, 1, 1);
    spriteData.texture = image->View();
}

// -------------------------------------------------------------------------------

Background::~Background()
{
    if (localImage)
        delete image;
}

// -------------------------------------------------------------------------------

void Background::Draw(ViewPort & vp)
{ 
    // define um sprite com a região do pano de fundo limitada pela viewport
    spriteData.width = uint(vp.right - vp.left);
    spriteData.height = uint(vp.bottom - vp.top);
    spriteData.texCoord.x = vp.left / float(image->Width());
    spriteData.texCoord.y = vp.top / float(image->Height());
    spriteData.texSize.x = spriteData.width / float(image->Width());
    spriteData.texSize.y = spriteData.height / float(image->Height());

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(spriteData);
}

// -------------------------------------------------------------------------------

