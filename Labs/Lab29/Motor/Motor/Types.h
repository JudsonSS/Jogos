/**********************************************************************************
// Types (Arquivo de Cabeçalho)
// 
// Criação:		02 Abr 2011
// Atualização:	02 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Isola os tipos específicos da plataforma fornecendo tipos
//				consistentes para o Motor de Jogo.
//
**********************************************************************************/

#ifndef _DESENVJOGOS_TYPES_H_
#define _DESENVJOGOS_TYPES_H_

#ifdef MOTOR_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

#pragma warning(disable: 4251)

// nomes para tipos padrões da linguagem C++ usados na engine
typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned long		ulong;
typedef long long			llong;
typedef unsigned long long	ullong;
typedef unsigned int		uint;

struct Canvas
{
	float width;			// largura da área do jogo
	float height;			// altura da área do jogo
	float centerX;			// centro da área do jogo no eixo x
	float centerY;			// centro da área do jogo no eixo y
};

struct DLL ViewPort
{
	float left;				// coordenada x1
	float top;				// coordenada y1
	float right;			// coordenada x2
	float bottom;			// coordenada y2
};

#endif