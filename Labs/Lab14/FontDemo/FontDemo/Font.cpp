/**********************************************************************************
// Font (Codigo Fonte)
//
// Criação:     07 Out 2011
// Atualização: 08 Set 2019
// Compilador:  Visual C++ 2019
//
// Descrição:   Uma classe para representar fontes e mostrar texto
//
**********************************************************************************/

#include "Engine.h"         // motor do jogo
#include "Font.h"           // definições da classe Font
#include <cmath>            // funções matemáticas
#include <fstream>          // entrada/sanída de arquivos
using namespace std;        // dispensa o uso do std::

// ---------------------------------------------------------------------------------

Font::Font(const string & filename)
{
    fontTiles = new TileSet(filename, 16, 16);
    ZeroMemory(spacing, sizeof(spacing));
    ZeroMemory(&sprite, sizeof(sprite));
    
    // inicialmente a largura de cada letra é fixa
    proportional = false;
    charWidth = fontTiles->TileWidth();
}

// -------------------------------------------------------------------------------

Font::~Font()
{
    delete fontTiles;
}

// -------------------------------------------------------------------------------    

void Font::Spacing(int width)
{
    proportional = false;
    charWidth = width;
}

// -------------------------------------------------------------------------------    

void Font::Spacing(const string & filename)
{
    // lê 512 bytes (2 bytes por caractere)
    ifstream fin;
    fin.open(filename.c_str(), ios_base::in | ios_base::binary);    
    fin.read((char*) spacing, 512);
    fin.close();

    proportional = true;
}

// -------------------------------------------------------------------------------    

void Font::Draw(float x, float y, string text, Color color, float depth, float scale, float rotation)
{
    // posição de início do texto
    float posX = x;
    float posY = y;

    // converte para radianos
    rotation = rotation * XM_PI / 180.0f;
    
    // número de caracteres no texto
    int textLength = int(text.size());
    
    // para cada caractere do texto
    for (int i = 0; i < textLength; ++i)
    {
        // caractere a ser exibido
        int frame = int (text[i]);

        // caracteres acentuados tem código deslocado
        if (frame < 0)
            frame += 256;

        // se foi carregado o espaçamento proporcional
        if (proportional)
            charWidth = spacing[frame];

        // configura sprite
        sprite.x = posX;
        sprite.y = posY;
        sprite.depth = depth;
        sprite.scale = scale;
        sprite.rotation = rotation;
        sprite.width = fontTiles->TileWidth();
        sprite.height = fontTiles->TileHeight();
        sprite.texSize.x = float(fontTiles->TileWidth()) / fontTiles->Width();
        sprite.texSize.y = float(fontTiles->TileHeight()) / fontTiles->Height();
        sprite.texture = fontTiles->View();
        sprite.texCoord.x = (frame % fontTiles->Columns()) * sprite.texSize.x;
        sprite.texCoord.y = (frame / fontTiles->Columns()) * sprite.texSize.y;
        sprite.color = color;

        // adiciona o sprite na lista de desenho
        Engine::renderer->Draw(sprite);

        // calcula posição do próximo caractere
        posX += charWidth * scale * cos(rotation);
        posY += charWidth * scale * sin(rotation);
    }
}

// -------------------------------------------------------------------------------