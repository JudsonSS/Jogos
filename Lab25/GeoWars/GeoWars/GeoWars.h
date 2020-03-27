/**********************************************************************************
// GeoWars (Arquivo de Cabeçalho)
// 
// Criação:		23 Out 2012
// Atualização:	05 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Demonstração de scrolling e IA
//
**********************************************************************************/

#ifndef _GEOWARS_H_
#define _GEOWARS_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, BLUE, GREEN, MAGENTA, ORANGE, WALLHIT };

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL };

// ------------------------------------------------------------------------------

class GeoWars : public Game
{
private:
	Background * backg = nullptr;	// pano de fundo
	Hud * hud = nullptr;			// heads up display
	bool viewBBox = false;			// bouding box visível

public:
	static Player * player;			// ponteiro para o jogador
	static Audio * audio;			// sitema de áudio
	static Scene * scene;			// cena do jogo
	static bool viewHUD;			// hud visível

	void Init();					// inicialização
	void Update();					// atualização
	void Draw();					// desenho
	void Finalize();				// finalização
};

// ---------------------------------------------------------------------------------

#endif