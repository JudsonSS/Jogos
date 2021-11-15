/**********************************************************************************
// Background (Arquivo de Cabeçalho)
// 
// Criação:     07 Dez 2011
// Atualização: 12 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Representa um pano de fundo maior que a janela
//
**********************************************************************************/

#ifndef _PROGJOGOS_BACKGROUND_H_
#define _PROGJOGOS_BACKGROUND_H_

#ifdef ENGINE_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// -------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Image.h"                      // carregamento de imagens
#include "Sprite.h"                     // desenho de sprites
#include <string>                       // biblioteca string da STL
using std::string;                      // permite usar string sem std::

// -------------------------------------------------------------------------------

class DLL Background
{
private:
    SpriteData spriteData;              // informações do sprite 
    const Image * image;                // imagem de fundo
    bool localImage;                    // imagem local ou externa

public:
    Background(string filename);        // construtor padrão
    Background(const Image* img);       // construtor a partir de imagem
    ~Background();                      // destrutor

    void Draw(ViewPort & sourceRect);   // desenha uma porção da imagem 
    float Width();                      // retorna a largura do pano de fundo
    float Height();                     // retorna a altura do pano de fundo
}; 

// ---------------------------------------------------------------------------------

// retorna a largura do sprite
inline float Background::Width()
{ return float(image->Width()); }

// retorna a altura do sprite
inline float Background::Height()
{ return float(image->Height()); }

// -------------------------------------------------------------------------------


#endif