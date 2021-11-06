/**********************************************************************************
// Sprite (Arquivo de Cabeçalho)
// 
// Criação:     11 Jul 2007
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para representar um sprite
//
**********************************************************************************/

#ifndef _PROGJOGOS_SPRITE_H_
#define _PROGJOGOS_SPRITE_H_

// ---------------------------------------------------------------------------------

#include "Image.h"
#include "Types.h"
#include <DirectXMath.h>
using namespace DirectX;

// ---------------------------------------------------------------------------------

struct Layer
{
    static const float FRONT;
    static const float UPPER;
    static const float MIDDLE;
    static const float LOWER;
    static const float BACK;
};

// definição de cor para o sprite
struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color() : 
        r(0), g(0), b(0), a(1) {}

    Color(float red, float green, float blue, float alpha) :
        r(red), g(green), b(blue), a(alpha) {}
};

// definição de um sprite
struct SpriteData
{
    float x, y;
    float scale;
    float depth;
    float rotation;
    uint  width;
    uint  height;
    ID3D11ShaderResourceView* texture;
    XMFLOAT2 texCoord;
    XMFLOAT2 texSize;
    Color color;

    SpriteData() :
        x(0), y(0),
        scale(0), depth(0), rotation(0),
        width(0), height(0),
        texture(nullptr),
        texCoord(XMFLOAT2(0, 0)),
        texSize(XMFLOAT2(0, 0)),
        color(Color(1, 1, 1, 1)) {}
};

// ---------------------------------------------------------------------------------

class Sprite
{
private:
    SpriteData sprite;              // dados do sprite 
    const Image * image;            // ponteiro para uma imagem
    bool localImage;                // imagem local ou externa

public:
    Sprite(string filename);        // constroi sprite a partir de um arquivo
    Sprite(const Image * img);      // constroi sprite a partir de imagem existente
    ~Sprite();                      // destrutor do sprite

    int Width();                    // largura do sprite
    int Height();                   // altura do sprite

    void Draw(                                                // desenha sprite
        float x, float y, float z = Layer::MIDDLE,            // coordenadas da tela
        float scale = 1.0f, float rotation = 0.0f,            // escala e rotação
        Color color = { 1, 1, 1, 1 });                        // efeito de cor

    void Draw(                                                // desenha sprite
        float x, float y, float z,                            // coordenadas da tela
        float scale, float rotation,                          // escala e rotação
        Color& color, RECT& region);                          // cor e região
};

// ---------------------------------------------------------------------------------
// Funções Inline

// retorna a largura do sprite
inline int Sprite::Width() 
{ return image->Width(); }

// retorna a altura do sprite
inline int Sprite::Height() 
{ return image->Height(); }

// ---------------------------------------------------------------------------------

#endif