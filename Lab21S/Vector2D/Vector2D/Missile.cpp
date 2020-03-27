/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:		23 Nov 2011
// Atualização:	16 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define uma classe para um míssil/projétil
//
**********************************************************************************/

#include "Missile.h"
#include "Vector2D.h"
#include <cmath>

// ------------------------------------------------------------------------------

Missile::Missile(Plane * plane, Image * img, float delta)
{
	// inicializa sprite
	sprite = new Sprite(img);

	// inicializa vetor velocidade
	speed.angle = plane->Angle() + delta;
	speed.magnitude = 500;
	
	// usa mesma rotação do avião
	rotation = plane->rotation;
	
	// move para posição
	MoveTo(plane->X() + 50 * cos(speed.Radians()), plane->Y() - 50 * sin(speed.Radians()));
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
	delete sprite;
}

// -------------------------------------------------------------------------------

void Missile::Update()
{
	Translate(speed.XCom() * gameTime, -speed.YCom() * gameTime);
	
	if (x > window->Width() || x < 0 || y > window->Height() || y < 0)
	{
		Vector2D::audio->Play(EXPLOSION);
		Vector2D::scene->Delete();
	}
}

// -------------------------------------------------------------------------------

void Missile::Draw()
{
	sprite->Draw(x, y, z, scale, rotation);
}

// -------------------------------------------------------------------------------
