/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:		10 Out 2012
// Atualização:	03 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "Missile.h"
#include "GeoWars.h"

// -------------------------------------------------------------------------------

Player::Player()
{
	// configuração do objeto
	sprite = new Sprite("Resources/Player.png");
	speed  = new Vector(90.0f, 0.0f);
	bbox   = new Circle(18.0f);
	MoveTo(game->CenterX(), game->CenterY());
	type = PLAYER;

	// configuração do emissor de partículas
	Emitter emitter;
	emitter.imgFile = "Resources/Star.png";		// arquivo de imagem
	emitter.angle = 270.0f;						// ângulo base do emissor
	emitter.spread = 25;						// espalhamento em graus
	emitter.lifeTime = 0.3f;					// tempo de vida em segundos
	emitter.genTime = 0.010f;					// tempo entre geração de novas partículas
	emitter.percToDim = 0.6f;					// desaparece após 60% da vida
	emitter.minSpeed = 50.0f;					// velocidade mínima das partículas
	emitter.maxSpeed = 100.0f;					// velocidade máxima das partículas
	emitter.r = 1.0f;							// componente Red da partícula 
	emitter.g = 1.0f;							// componente Green da partícula 
	emitter.b = 1.0f;							// componente Blue da partícula 
	emitter.a = 1.0f;							// transparência da partícula

	// cria sistema de partículas
	tail = new Particles(emitter);
}

// -------------------------------------------------------------------------------

Player::~Player()
{
	delete sprite;
	delete speed;
	delete bbox;
	delete tail;
}

// -------------------------------------------------------------------------------

void Player::Move(Vector && v)
{
	speed->Add(v);

	// limita velocidade máxima
	if (speed->magnitude > 10.0f)
		speed->magnitude = 10.0f;

}

// -------------------------------------------------------------------------------

void Player::Update()
{
	// magnitude do vetor aceleração
	float accel = 40.0f * gameTime;

	// modifica vetor velocidade do player
	if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_UP))
		Move(Vector(45.0f, accel));
	else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_UP))
		Move(Vector(135.0f, accel));
	else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_DOWN))
		Move(Vector(225.0f, accel));
	else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_DOWN))
		Move(Vector(315.0f, accel));
	else if (window->KeyDown(VK_RIGHT))
		Move(Vector(0.0f, accel));
	else if (window->KeyDown(VK_LEFT))
		Move(Vector(180.0f, accel));
	else if (window->KeyDown(VK_UP))
		Move(Vector(90.0f, accel));
	else if (window->KeyDown(VK_DOWN))
		Move(Vector(270.0f, accel));
	else
		// se nenhuma tecla está pressionada comece a frear
		if (speed->magnitude > 0.1f)
			Move(Vector(speed->angle + 180.0f, 5.0f * gameTime));
		else
			// velocidade muita baixa, não use soma vetorial, apenas pare
			speed->magnitude = 0.0f;
	
	// movimenta objeto pelo seu vetor velocidade
	Translate(speed->XCom() * 50.0f * gameTime, -speed->YCom() * 50.0f * gameTime);

	// dispara míssil
	if (window->KeyCtrl(VK_SPACE))
	{
		GeoWars::audio->Play(FIRE);
		GeoWars::scene->Add(new Missile(), STATIC);
	}

	// atualiza calda do jogador
	tail->Generator().angle = speed->angle + 180;
	tail->Generate(x - 10 * cos(speed->Radians()), y + 10 * sin(speed->Radians()));
	tail->Update(gameTime);

	// restringe a área do jogo
	if (x < 50)
		MoveTo(50, y);
	if (y < 50)
		MoveTo(x, 50);
	if (x > game->Width() - 50)
		MoveTo(game->Width() - 50, y);
	if (y > game->Height() - 50)
		MoveTo(x, game->Height() - 50);
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
	sprite->Draw(x, y, Layer::MIDDLE, 1.0f, -speed->angle + 90.0f);
	tail->Draw(Layer::MIDBACK, 1.0f);
}


// -------------------------------------------------------------------------------
