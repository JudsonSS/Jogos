/**********************************************************************************
// Background (Arquivo de Cabe�alho)
// 
// Cria��o:		07 Dez 2011
// Atualiza��o:	02 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Representa um pano de fundo maior que a janela
//
**********************************************************************************/

#ifndef _DESENVJOGOS_BACKGROUND_H_
#define _DESENVJOGOS_BACKGROUND_H_

#ifdef MOTOR_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// -------------------------------------------------------------------------------

#include "Types.h"						// tipos espec�ficos da engine
#include "Image.h"						// carregamento de imagens
#include "Sprite.h"						// desenho de sprites
#include <string>						// biblioteca string da STL
using std::string;						// permite usar string sem std::

// -------------------------------------------------------------------------------

class DLL Background
{
private:
	SpriteData spriteData;				// informa��es do sprite 
	const Image * image;				// imagem de fundo

public:
	Background(string filename);		// construtor	
	~Background();						// destrutor

	void Draw(ViewPort & sourceRect);	// desenha uma por��o da imagem 
	uint Width();						// retorna a largura do pano de fundo
    uint Height();						// retorna a altura do pano de fundo
}; 

// ---------------------------------------------------------------------------------

// retorna a largura do sprite
inline uint Background::Width() 
{ return image->Width(); }

// retorna a altura do sprite
inline uint Background::Height() 
{ return image->Height(); }

// -------------------------------------------------------------------------------


#endif