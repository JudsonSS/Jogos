/**********************************************************************************
// Object (Arquivo de Cabeçalho)
//
// Criação:		01 Out 2007
// Atualização:	12 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Essa é a classe base para todos objetos do jogo.
//
//				Um objeto do jogo é qualquer coisa que possámos querer desenhar
//				ou interagir dentro do jogo. Por exemplo, um soldado, um prédio,
//				um projétil, uma forma geométrica, etc.
//
**********************************************************************************/

#ifndef _DESENVJOGOS_OBJECT_H_
#define _DESENVJOGOS_OBJECT_H_

#ifdef MOTOR_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// -----------------------------------------------------------------------------

#include "Types.h"				// tipos específicos do motor
#include "Game.h"				// representação de um jogo
#include "Window.h"				// janela utilizada no jogo
#include "Geometry.h"			// geometria para a bounding box

// -----------------------------------------------------------------------------

class DLL Object
{
protected:
	static Window* & window;	// janela do jogo
	static Game*   & game;		// jogo em que o objeto está inserido
	static float   & gameTime;	// tempo do último quadro

	float x, y, z;				// coordenadas do objeto
	float scale;				// escala do objeto
	float rotation;				// rotação do objeto
	uint type;					// tipo do objeto
	Geometry * bbox;			// bounding box do objeto

public:
	Object();					// construtor padrão de um objeto
	virtual ~Object();			// destrutor virtual

	// ------------------------
	// funções virtuais	
	// ------------------------
	// podem ser sobrescritas na classe derivada
	// e chamadas corretamente mesmo usando um
	// ponteiro para a classe base

	// retorna coordenada x do objeto
	virtual float X() const;

	// retorna coordenada y do objeto
	virtual float Y() const;

	// retorna coordenada z do objeto
	virtual float Z() const;

	// retorna a escala do objeto
	virtual float Scale() const;

	// retorna a rotação do objeto
	virtual float Rotation() const;

	// retorna tipo do objeto
	virtual uint Type() const;

	// retorna a bounding box do objeto
	virtual Geometry * BBox() const;

	// move o objeto por (dx, dy, dz)
	virtual void Translate(float dx, float dy, float dz = 0.0f);

	// move o objeto para as coordenadas (px, py, pz)
	virtual void MoveTo(float px, float py, float pz);

	// move o objeto para as coordenadas (px, py)
	virtual void MoveTo(float px, float py);

	// amplia ou reduz objeto pelo fator
	virtual void Scale(float factor);

	// ajusta escala para novo valor
	virtual void ScaleTo(float factor);

	// rotaciona geometria pelo ângulo
	virtual void Rotate(float angle);

	// ajusta rotação para novo valor
	virtual void RotateTo(float angle);

	// faz a resolução de colisão do objeto
	virtual void OnCollision(Object * obj);

	// ------------------------
	// funções virtuais puras	
	// ------------------------	 
	// devem ser obrigatoriamente sobrescritas na classe derivada

	// atualiza estado do objeto
	virtual void Update() = 0;

	// desenha o objeto na tela
	virtual void Draw() = 0;
};

// -----------------------------------------------------------------------------
// Métodos Inline

// retorna coordenada x do objeto
inline float Object::X() const
{ return x; }

// retorna coordenada y do objeto
inline float Object::Y() const
{ return y; }

// retorna coordenada z do objeto
inline float Object::Z() const
{ return z; }

// retorna a escala do objeto
inline float Object::Scale() const
{ return scale; }

// retorna a rotação do objeto
inline float Object::Rotation() const
{ return rotation; }

// retorna o tipo do objeto
inline uint Object::Type() const
{ return type; }

// retorna a bounding box do objeto
inline Geometry * Object::BBox() const
{ return bbox; }

// -----------------------------------------------------------------------------

#endif


