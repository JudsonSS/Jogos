/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:		25 Mar 2013
// Atualização:	10 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "Missile.h"
#include "Patterns.h"

// -------------------------------------------------------------------------------

TileSet * Player::exploSet = nullptr;

// -------------------------------------------------------------------------------

Player::Player()
{
	// carrega tilesets, imagens e sprites
	exploSet = new TileSet("Resources/Explosion.png", 60, 60, 5, 5);
	missile = new Image("Resources/Missile.png");
	sprite = new Sprite("Resources/Nave.png");
	MoveTo(window->CenterX(), window->Height() - 30.0f);
	type = PLAYER;
}

// -------------------------------------------------------------------------------

Player::~Player()
{
	delete exploSet;
	delete missile;
	delete sprite;
	delete bbox;
}

// -------------------------------------------------------------------------------

void Player::Update()
{
	// deslocamento padrão
	float delta = 250 * gameTime;

	// dispara um míssil com a barra de espaço
	if (window->KeyCtrl(VK_SPACE))
	{
		// tamanho da nave é 30x30
		Missile * firing = new Missile(missile);
		firing->MoveTo(x, y - 15, Layer::MIDFRONT);
		Patterns::scene->Add(firing, STATIC);
		Patterns::audio->Play(MISSILE);
	}

	// movimenta player
	if (window->KeyDown(VK_RIGHT))
		Translate(delta, 0);
	else if (window->KeyDown(VK_LEFT))
		Translate(-delta, 0);
	
	// mantém player dentro da tela
	if (x - 15 < 0)
		MoveTo(15, y);
	if (x + 15 > window->Width())
		MoveTo(window->Width() - 15, y);
}

// -------------------------------------------------------------------------------
