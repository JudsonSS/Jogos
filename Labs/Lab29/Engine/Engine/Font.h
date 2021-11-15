/**********************************************************************************
// Font (Arquivo de Cabeçalho)
//
// Criação:     07 Out 2011
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Uma classe para representar fontes e mostrar texto
//
**********************************************************************************/

#ifndef _PROGJOGOS_FONT_H_
#define _PROGJOGOS_FONT_H_

#ifdef ENGINE_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// ---------------------------------------------------------------------------------

#include "TileSet.h"                            // folha de sprites
#include "Sprite.h"                             // desenho de sprites
#include "Types.h"                              // tipos do motor de jogos
#include <string>                               // inclui a classe string da STL
using std::string;                              // dispensa o uso do std::

// ---------------------------------------------------------------------------------

class DLL Font
{
private:
    TileSet * fontTiles;                        // folha de caracteres
    SpriteData sprite;                          // sprite para desenho 
    short spacing[256];                         // largura de cada caractere da folha
    bool proportional;                          // usando espaçamento proporcional
    int  charWidth;                             // largura de cada caractere
    
public:
    Font(const string & filename);              // construtor
    ~Font();                                    // destrutor

    void Spacing(int width);                    // valor fixo para o espaçamento 
    void Spacing(const string & filename);      // ajusta espaçamento entre letras    

    void Draw(                                  // exibe texto na tela
        float x,                                // posição x do texto
        float y,                                // posição y do texto
        string text,                            // string a ser exibida
        Color color = { 1, 1, 1, 1 },           // cor do texto
        float depth = 0.0f,                     // profundidade do texto
        float scale = 1.0f,                     // escala do texto
        float rotation = 0.0f);                 // rotação do texto   
};

// ---------------------------------------------------------------------------------

#endif