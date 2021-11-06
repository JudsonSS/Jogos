/**********************************************************************************
// Sprite (Código Fonte)
// 
// Criação:     11 Jul 2007
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para representar um sprite
//
**********************************************************************************/

#include "Sprite.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de membros estáticos das classes

// Valores de profundidade predefinidos: 
//  - A profundidade 0.00 é reservada para o desenho de texto
//  - A profundidade 0.01 é reservada para as bounding boxes
//  - O valor máximo deve ser menor que 1.00

const float Layer::FRONT  = 0.02f;
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

void Sprite::Draw(float x, float y, float z, float scale, float rotation, Color color)
{
    // ajusta coordenadas usando a viewport
    x -= Engine::game->viewport.left;
    y -= Engine::game->viewport.top;

    // configura sprite
    sprite.x = x;
    sprite.y = y;
    sprite.scale = scale;
    sprite.depth = z;
    sprite.rotation = rotation * XM_PI / 180.0f;
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texCoord.x = 0;
    sprite.texCoord.y = 0;
    sprite.texSize.x = 1;
    sprite.texSize.y = 1;
    sprite.color = color;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(sprite);
}

// ---------------------------------------------------------------------------------

void Sprite::Draw(float x, float y, float z, float scale, float rotation, Color & color, RECT & region)
{
    // ajusta coordenadas usando a viewport
    x -= Engine::game->viewport.left;
    y -= Engine::game->viewport.top;

    sprite.x = x;
    sprite.y = y;
    sprite.scale = scale;
    sprite.depth = z;
    sprite.rotation = rotation * XM_PI / 180.0f;
    sprite.width = region.right - region.left;
    sprite.height = region.bottom - region.top;
    sprite.texCoord.x = float(region.left) / image->Width();
    sprite.texCoord.y = float(region.top) / image->Height();
    sprite.texSize.x = float(sprite.width) / image->Width();
    sprite.texSize.y = float(sprite.height) / image->Height();
    sprite.color = color;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(sprite);
}

// ---------------------------------------------------------------------------------