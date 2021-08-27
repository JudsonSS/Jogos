/**********************************************************************************
// Sprite (Código Fonte)
// 
// Criação:     11 Jul 2007
// Atualização: 27 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para representar um sprite
//
**********************************************************************************/

#include "Sprite.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de membros estáticos das classes

// valores de profundidade predefinidos
const float Layer::FRONT  = 0.01f;
const float Layer::UPPER  = 0.25f;
const float Layer::MIDDLE = 0.50f;
const float Layer::LOWER  = 0.75f;
const float Layer::BACK   = 0.99f;

// ---------------------------------------------------------------------------------

Sprite::Sprite(string filename)
{
    // carrega imagem
    image = new Image(filename);
    localImage = true;
    
    // configura registro sprite
    sprite.texture = image->View();
}

// ---------------------------------------------------------------------------------

Sprite::Sprite(const Image * img)
{
    // aponta para imagem externa
    image = img;
    localImage = false;

    // configura registro sprite
    sprite.texture = image->View();
}

// ---------------------------------------------------------------------------------

Sprite::~Sprite()
{
    if (localImage)
        delete image;
}

// ---------------------------------------------------------------------------------

void Sprite::Draw(float x, float y, float z)
{
    sprite.x = x;
    sprite.y = y;
    sprite.scale = 1.0f;
    sprite.depth = z;
    sprite.rotation = 0.0f;
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texCoord.x = 0;
    sprite.texCoord.y = 0;
    sprite.texSize.x = 1;
    sprite.texSize.y = 1;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(&sprite);
}

// ---------------------------------------------------------------------------------