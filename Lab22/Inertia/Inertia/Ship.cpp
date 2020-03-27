/**********************************************************************************
// Ship (C�digo Fonte)
// 
// Cria��o:		01 Out 2012
// Atualiza��o:	19 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descri��o:	Define uma nave espacial
//
**********************************************************************************/

#include "Ship.h"
#include "Missile.h"
#include "Inertia.h"

// ---------------------------------------------------------------------------------

Ship::Ship()
{
	// inicializa anima��o 
	shipSet = new TileSet("Resources/SpaceShip.png", 43, 60, 6, 6);
	shipAni = new Animation(shipSet, 0.060f, false); 

	uint seqInertia[] = {0};
	uint seqForwThrust[] = {1,2,3,4};
	uint seqBackThrust[] = {5};

	shipAni->Add(FORWARD, seqForwThrust, 4);
	shipAni->Add(BACKWARD, seqBackThrust, 1);
	shipAni->Add(INERTIA, seqInertia, 1);

	// posi��o inicial da nave
	MoveTo(window->CenterX(), window->CenterY());

	// escala e rota��o da nave
	scale = 0.8f; 
	rotation = 0;
	
	// inicializa dire��o e velocidade da nave
	direction.angle = 90.0f;
	direction.magnitude = 10.0f;
	speed.angle = 90.0f;
	speed.magnitude = 0.0f;
}

// ---------------------------------------------------------------------------------

Ship::~Ship()
{
	delete shipSet;
	delete shipAni;
}

// ---------------------------------------------------------------------------------

void Ship::Forward()
{
	// impulsiona nave para frente
	direction.magnitude = 20.0f * gameTime;
	speed.Add(direction);
}

// ---------------------------------------------------------------------------------

void Ship::Backward()
{
	// impulsiona nave para tr�s
	Vector thrust;
	thrust.angle = direction.angle < 180 ?  direction.angle + 180.0f : direction.angle - 180.0f;
	thrust.magnitude = 10.0f * gameTime;
	speed.Add(thrust);	
} 

// ---------------------------------------------------------------------------------

void Ship::Rotate(float angle)
{
	// rotaciona vetor e objeto
	rotation += angle;
	direction.Rotate(angle);
}

// -------------------------------------------------------------------------------

void Ship::Update()
{
	// deslocamento padr�o
	float delta = 100 * gameTime;

	// rotaciona nave
	if (window->KeyDown(VK_RIGHT))
		Rotate(delta);
	if (window->KeyDown(VK_LEFT))
		Rotate(-delta);
	
	// impulsiona nave
	if (window->KeyDown(VK_UP))
		Forward();
	if (window->KeyDown(VK_DOWN))
		Backward();

	// sons e anima��o (usam KeyCtrl)
	if (window->KeyCtrl(VK_UP))
	{
		Inertia::audio->Play(JETUP);
		Inertia::audio->Play(LOOPUP, true);
		shipAni->Select(FORWARD);
	}
	if (window->KeyCtrl(VK_DOWN))
	{
		Inertia::audio->Play(JETDOWN);
		Inertia::audio->Play(LOOPDOWN, true);
		shipAni->Select(BACKWARD);
	}

	// libera��o de teclas
	if (window->KeyUp(VK_UP) && window->KeyUp(VK_DOWN))
		shipAni->Select(INERTIA);
	if (window->KeyUp(VK_UP))
	{
		Inertia::audio->Stop(JETUP);
		Inertia::audio->Stop(LOOPUP);
	}
	if (window->KeyUp(VK_DOWN))
	{
		Inertia::audio->Stop(JETDOWN);
		Inertia::audio->Stop(LOOPDOWN);
	}

	// dispara m�ssil
	if (window->KeyCtrl(VK_SPACE))
	{
		Inertia::audio->Play(FIRE);
		Inertia::scene->Add(new Missile(this), MOVING);
	}

	// in�rcia desloca constantemente a nave atrav�s do vetor speed
	Translate(speed.XCom() * 0.1f * delta, -speed.YCom() * 0.1f * delta);	

	// faz a nave girar ao redor da tela
	if (x < 0)
		Translate(float(window->Width()), 0.0f);
	if (x > window->Width())
		Translate(float(-window->Width()), 0.0f);
	if (y < 0)
		Translate(0.0f, float(window->Height()));
	if (y > window->Height())
		Translate(0.0f, float(-window->Height()));
	
	// atualiza anima��o
	if (!shipAni->Inactive())
		shipAni->NextFrame();
}

// -------------------------------------------------------------------------------

void Ship::Draw()
{
	// desenha nave espacial 
	shipAni->Draw(x, y, z, scale, rotation);
}

// -------------------------------------------------------------------------------