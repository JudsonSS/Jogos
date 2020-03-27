/**********************************************************************************
// Sprite (Arquivo de Cabe�alho)
// 
// Cria��o:		11 Jul 2007
// Atualiza��o: 12 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Define uma classe para representar um sprite
//
**********************************************************************************/

#ifndef _DESENVJOGOS_SPRITE_H_
#define _DESENVJOGOS_SPRITE_H_

#ifdef MOTOR_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// ---------------------------------------------------------------------------------

#include "Image.h"
#include "Types.h"
#include <DirectXMath.h>
using namespace DirectX;

// ---------------------------------------------------------------------------------

// defini��o de camadas para os sprites
struct DLL Layer
{
	static const float FRONT;
	static const float MIDFRONT;
	static const float MIDDLE;
	static const float MIDBACK;
	static const float BACK;
};

// defini��o de cor para o sprite
struct DLL Color
{
	float r;
	float g;
	float b;
	float a;

	Color(float red, float green, float blue, float alpha) :
		r(red), g(green), b(blue), a(alpha) {}
};

// defini��o de um sprite
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

class DLL Sprite
{
private:
	SpriteData sprite;										// dados do sprite 
	bool localImage;										// imagem local ou externa
	const Image * image;									// ponteiro para imagem

public:
	Sprite(string filename);								// constroi sprite a partir de um arquivo
	Sprite(const Image * img);								// constroi sprite a partir de imagem existente
	~Sprite();												// destrutor do sprite

	int Width();											// largura do sprite
	int Height();											// altura do sprite

	void Draw(												// desenha sprite
		float x, float y, float z = Layer::MIDDLE,			// coordenadas da tela
		float scale = 1.0f, float rotation = 0.0f,			// escala e rota��o
		Color color = { 1, 1, 1, 1 });						// efeito de cor

	void Draw(												// desenha sprite
		float x, float y, float z,							// coordenadas da tela
		float scale, float rotation,						// escala e rota��o
		Color& color, RECT& region);						// cor e regi�o
};

// ---------------------------------------------------------------------------------
// Fun��es Inline

// retorna a largura do sprite
inline int Sprite::Width() 
{ return image->Width(); }

// retorna a altura do sprite
inline int Sprite::Height() 
{ return image->Height(); }

// ---------------------------------------------------------------------------------

#endif