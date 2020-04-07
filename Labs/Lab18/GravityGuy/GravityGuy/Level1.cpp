/**********************************************************************************
// Level1 (Código Fonte) 
// 
// Criação:		14 Fev 2013
// Atualização:	04 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Nível 1 do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "GravityGuy.h"
#include "Home.h"
#include "Level1.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

// inicializa membros da classe
Scene * Level1::scene = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
	// cria gerenciador de cena
	scene = new Scene();

	// pano de fundo do jogo
	backg = new Background();
	scene->Add(backg, STATIC);

	// cria jogador
	player = new Player();
	scene->Add(player, MOVING);

	// ----------------------
	// cria plataformas
	// ----------------------

	Platform * plat;
	float posX, posY;
	uint  platType;
	ifstream fin;

	fin.open("Level1.txt");
	fin >> posX;
	while (!fin.eof())
	{
		if (fin.good())
		{
			// lê linha com informações da plataforma
			fin >> posY; fin >> platType;
			plat = new Platform(posX, posY, platType);
			scene->Add(plat, STATIC);
		}
		else
		{
			// ignora comentários
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}

		fin >> posX;
	}
	fin.close();

	// ----------------------

	// toca música
	GravityGuy::audio->Play(MUSIC);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
	if (window->KeyCtrl(VK_ESCAPE))
	{
		GravityGuy::audio->Stop(MUSIC);
		GravityGuy::NextLevel<Home>();
	}
	else if (player->Bottom() < 0 || player->Top() > window->Height() || window->KeyCtrl('N'))
	{
		GravityGuy::audio->Stop(MUSIC);
		GravityGuy::NextLevel<GameOver>();
	}
	else
	{
		scene->Update();
		scene->CollisionDetection();
	}
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
	backg->Draw();
	scene->Draw();

	if (GravityGuy::viewBBox)
	{
		// desenha bounding box dos objetos
		Engine::renderer->BeginPixels();
		scene->Begin();
		Object * obj = nullptr;
		while (obj = scene->Next())
			if (obj->bbox)
				Engine::renderer->Draw(obj->bbox, 0xffff00ff);
		Engine::renderer->EndPixels();
	}
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
	delete scene;
}

// ------------------------------------------------------------------------------
