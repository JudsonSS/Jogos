/**********************************************************************************
// Ship (Código Fonte)
// 
// Criação:		01 Out 2012
// Atualização:	19 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define uma nave espacial
//
**********************************************************************************/

#include "Ship.h"
#include "Missile.h"
#include "Asteroids.h"

// ---------------------------------------------------------------------------------

Ship::Ship()
{
	// inicializa animação 
	shipSet = new TileSet("Resources/SpaceShip.png", 43, 60, 6, 6);
	shipAni = new Animation(shipSet, 0.060f, false); 

	uint seqInertia[] = {0};
	uint seqForwThrust[] = {1,2,3,4};
	uint seqBackThrust[] = {5};

	shipAni->Add(FORWARD, seqForwThrust, 4);
	shipAni->Add(BACKWARD, seqBackThrust, 1);
	shipAni->Add(INERTIA, seqInertia, 1);

	// cria bounding box
	Point shipVertex[4] = { Point(0, -25), Point(18, 15), Point(0, 11), Point(-18, 15) };
	bbox = new Poly(shipVertex, 4);

	/*bbox = new Rect(
		-1.0f * shipSet->TileWidth() / 2.0f,
		-1.0f * shipSet->TileHeight() / 2.0f,
		shipSet->TileWidth() / 2.0f,
		shipSet->TileHeight() / 2.0f);*/

	// posição inicial da nave
	MoveTo(window->CenterX(), window->CenterY());

	// escala e rotação da nave
	scale = 0.8f; 
	rotation = 0;
	
	// inicializa direção e velocidade da nave
	direction.angle = 90.0f;
	direction.magnitude = 10.0f;
	speed.angle = 90.0f;
	speed.magnitude = 0.0f;

	// tipo do objeto
	type = SHIP;
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
	// impulsiona nave para trás
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
	
	if (bbox)
		bbox->Rotate(angle);
}

// -------------------------------------------------------------------------------

void Ship::Update()
{
	// deslocamento padrão
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

	// sons e animação (usam KeyCtrl)
	if (window->KeyCtrl(VK_UP))
	{
		Asteroids::audio->Play(JETUP);
		Asteroids::audio->Play(LOOPUP, true);
		shipAni->Select(FORWARD);
	}
	if (window->KeyCtrl(VK_DOWN))
	{
		Asteroids::audio->Play(JETDOWN);
		Asteroids::audio->Play(LOOPDOWN, true);
		shipAni->Select(BACKWARD);
	}

	// liberação de teclas
	if (window->KeyUp(VK_UP) && window->KeyUp(VK_DOWN))
		shipAni->Select(INERTIA);
	if (window->KeyUp(VK_UP))
	{
		Asteroids::audio->Stop(JETUP);
		Asteroids::audio->Stop(LOOPUP);
	}
	if (window->KeyUp(VK_DOWN))
	{
		Asteroids::audio->Stop(JETDOWN);
		Asteroids::audio->Stop(LOOPDOWN);
	}

	// dispara míssil
	if (window->KeyCtrl(VK_SPACE))
	{
		Asteroids::audio->Play(FIRE);
		Asteroids::scene->Add(new Missile(this), MOVING);
	}

	// inércia desloca constantemente a nave através do vetor speed
	Translate(speed.XCom() * 0.1f * delta, -speed.YCom() * 0.1f * delta);	

	// faz a nave girar ao redor da tela
	if (x + 24.0f < 0)
		MoveTo(window->Width() + 24.0f, y);
	if (x - 24.0f > window->Width())
		MoveTo(-24.0f, y);
	if (y + 24.0f < 0)
		MoveTo(x, window->Height() + 24.0f);
	if (y - 24.0f > window->Height())
		MoveTo(x, -24.0f);
	
	// atualiza animação
	if (!shipAni->Inactive())
		shipAni->NextFrame();
}

// -------------------------------------------------------------------------------

void Ship::Draw()
{
	// desenha nave espacial 
	shipAni->Draw(x, y, Layer::MIDBACK, scale, rotation);
}

// -------------------------------------------------------------------------------