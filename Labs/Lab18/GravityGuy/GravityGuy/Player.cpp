/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:		20 Abr 2012
// Atualização:	04 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define uma classe para o jogador 
//
**********************************************************************************/

#include "Player.h"
#include "GravityGuy.h"
#include "GameOver.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
	tileset = new TileSet("Resources/GravityGuy.png", 32, 48, 5, 10);
	anim = new Animation(tileset, 0.120f, true);

	// seqüências de animação do player
	uint invert[4] = {6,7,8,9};
	uint normal[4] = {1,2,3,4};

	anim->Add(INVERTED, invert, 4);
	anim->Add(NORMAL, normal, 4);

	// cria bounding box
	bbox = new Rect(
		-1.0f * tileset->TileWidth() / 2.0f,
		-1.0f * tileset->TileHeight() / 2.0f,
		tileset->TileWidth() / 2.0f,
		tileset->TileHeight() / 2.0f);
	
	// inicializa estado do player
	gravity = NORMAL;	

	// posição inicial
	MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete bbox;
	delete anim;
	delete tileset;	
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
	// mantém personagem na posição correta em cima da plataforma
	if (gravity == NORMAL)
		MoveTo(window->CenterX(), obj->Y() - 32);
	else
		MoveTo(window->CenterX(), obj->Y() + 32);

	// ----------------------------------------------------------
	// Processa teclas pressionadas
	// ----------------------------------------------------------
	// jogador só pode alterar a gravidade enquanto estiver
	// em cima de uma plataforma, não é possível a mudança no ar

	if (window->KeyCtrl(VK_SPACE))
	{
		gravity = !gravity;

		// toca efeito sonoro
		GravityGuy::audio->Play(TRANSITION);

		// tira player da plataforma para evitar 
		// detecção de colisão no quadro seguinte
		if (gravity == NORMAL)
			Translate(0, 12);
		else
			Translate(0 , -12);
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	// ----------------------------------------------------
	// ação da gravidade sobre o personagem
	// ----------------------------------------------------
	if (gravity == NORMAL)	
		Translate(0, 300 * gameTime);
	else
		Translate(0, -300 * gameTime);

	// atualiza animação
	anim->Select(gravity);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------