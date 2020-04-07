/**********************************************************************************
// Object (Código Fonte)
//
// Criação:		01 Out 2007
// Atualização:	31 Mai 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Essa é a classe base para todos objetos do jogo.
//
//				Um objeto do jogo é qualquer coisa que possámos querer desenhar
//				ou interagir dentro do jogo. Por exemplo, um soldado, um prédio,
//				um projétil, uma forma geométrica, etc.
//
**********************************************************************************/

#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

// apontador para a janela do jogo
Window * Object::window   = nullptr;				// ponteiro para a janela
float &  Object::gameTime = Engine::frameTime;		// tempo do último quadro

// -------------------------------------------------------------------------------

Object::Object()
{
	// posição do objeto
	x = y = 0.0f;

	// profundidade do objeto
	z = 0.5f;

	//tipo do objeto
	type = 0;

	// bounding box do objeto
	bbox = nullptr;

	if (!window)
		window = Engine::window;
}

// -------------------------------------------------------------------------------

Object::~Object()
{
}

// -------------------------------------------------------------------------------

void Object::Translate(float dx, float dy, float dz)
{
	x += dx;
	y += dy;
	z += dz;

	if (bbox)
		bbox->Translate(dx, dy);
}

// -------------------------------------------------------------------------------

void Object::MoveTo(float px, float py, float pz)
{
	x = px;
	y = py;
	z = pz;

	if (bbox)
		bbox->MoveTo(px, py);
}

// -------------------------------------------------------------------------------

void Object::MoveTo(float px, float py)
{
	x = px;
	y = py;

	if (bbox)
		bbox->MoveTo(px, py);
}

// -------------------------------------------------------------------------------

void Object::OnCollision(Object* obj)
{
}

// -------------------------------------------------------------------------------