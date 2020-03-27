/**********************************************************************************
// Sprite (C�digo Fonte)
// 
// Cria��o:		11 Jul 2007
// Atualiza��o: 13 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Define uma classe para representar um sprite
//
**********************************************************************************/

#include "Sprite.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos das classes

// valores de profundidade predefinidos: a profundidade zero (0.00) � reservada
// para o sprite que cont�m o desenho das bounding boxes dos objetos. O valor
// m�ximo deve ser menor que 1.00
const float Layer::FRONT    = 0.01f;
const float Layer::MIDFRONT = 0.25f;
const float Layer::MIDDLE   = 0.50f;
const float Layer::MIDBACK  = 0.75f;
const float Layer::BACK     = 0.99f;

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
	sprite.x = x;
	sprite.y = y;
	sprite.scale = scale;
	sprite.depth = z;
	sprite.rotation = rotation;
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