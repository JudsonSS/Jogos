/**********************************************************************************
// WavesDemo (Arquivo de Cabeçalho)
// 
// Criação:		23 Out 2012
// Atualização:	07 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Demonstração de movimento retilíneo
//
**********************************************************************************/

#ifndef _WAVESDEMO_H_
#define _WAVESDEMO_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Sprite.h"
#include "Player.h"
#include "Hud.h"


// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, MISSILE, ORANGE, WALLHIT };

enum SoundIds { THEME, FIRE, EXPLODE, HITWALL, SPAWN };

// ------------------------------------------------------------------------------

class WavesDemo : public Game
{
private:
	Sprite * backg = nullptr;		// pano de fundo
	Hud * hud = nullptr;			// heads up display	
	bool viewBBox = false;			// bouding box visível

public:
	static Audio * audio;			// sitema de áudio
	static Scene * scene;			// cena do jogo
	static Player* player;			// ponteiro para o jogador

	void Init();					// inicialização
	void Update();					// atualização
	void Draw();					// desenho
	void Finalize();				// finalização
};

// ---------------------------------------------------------------------------------

#endif