/**********************************************************************************
// Image (Arquivo de Cabeçalho)
// 
// Criação:     16 Mar 2012
// Atualização: 14 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para representar imagens
//
**********************************************************************************/

#ifndef _PROGJOGOS_IMAGE_H_
#define _PROGJOGOS_IMAGE_H_

#ifdef ENGINE_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"        // tipos específicos do motor
#include "Texture.h"      // função para carregar textura
#include <string>         // classe string de C++
using std::string;        // classe pode ser usada sem std::

// ---------------------------------------------------------------------------------

class DLL Image
{
private:
    ID3D11ShaderResourceView * textureView;      // view associada a textura
    uint width;                                  // altura da imagem
    uint height;                                 // largura da imagem

public:
    Image(string filename);                      // constroi imagem a partir de um arquivo

    Image(string filename,                       // arquivo que contém os blocos de imagem
        uint tileWidth,                          // largura dos blocos
        uint tileHeight,                         // altura dos blocos
        uint numColumns,                         // número de colunas 
        int* tiledMap,                           // matriz para montagem dos blocos
        uint tiledMapCols,                       // número de colunas da matriz
        uint tiledMapRows);                      // número de linhas da matriz

    ~Image();                                    // destrutor

    uint Width() const;                          // retorna largura da imagem
    uint Height() const;                         // retorna altura da imagem
    ID3D11ShaderResourceView * View() const;     // retorna ponteiro para a view da imagem
};

// ---------------------------------------------------------------------------------
// Métodos Inline

// retorna largura da textura
inline uint Image::Width() const
{ return width; }

// retorna altura da textura
inline uint Image::Height() const
{ return height; }

// retorna ponteiro para textura D3D
inline ID3D11ShaderResourceView * Image::View() const
{ return textureView; }

// --------------------------------------------------------------------------------

#endif




