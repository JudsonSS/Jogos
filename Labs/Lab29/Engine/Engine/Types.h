/**********************************************************************************
// Types (Arquivo de Cabeçalho)
// 
// Criação:     02 Abr 2011
// Atualização: 15 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Isola os tipos específicos da plataforma fornecendo tipos
//              consistentes para o Motor de Jogo.
//
**********************************************************************************/

#ifndef _PROGJOGOS_TYPES_H_
#define _PROGJOGOS_TYPES_H_

#ifdef ENGINE_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// desabilita mensagem dll-interface para membros da STL
#pragma warning(disable: 4251)

// nomes para tipos padrões da linguagem C++ usados na engine
using uchar  = unsigned char;
using ushort = unsigned short;
using ulong  = unsigned long;
using llong  = long long;
using ullong = unsigned long long;
using uint   = unsigned int;

struct Canvas
{
    float width;        // largura da área do jogo
    float height;       // altura da área do jogo
    float centerX;      // centro da área do jogo no eixo x
    float centerY;      // centro da área do jogo no eixo y
};

struct DLL ViewPort
{
    float left;         // coordenada x1
    float top;          // coordenada y1
    float right;        // coordenada x2
    float bottom;       // coordenada y2
};

#endif