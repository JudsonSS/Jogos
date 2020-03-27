/**********************************************************************************
// Balloons (Arquivo de Cabeçalho)
// 
// Criação:		28 Out 2011
// Atualização:	03 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Exemplo de uso do mouse e teclado
//
**********************************************************************************/

#ifndef _BALLOONS_H_
#define _BALLOONS_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Scene.h"
#include "Audio.h"
#include "Font.h"
#include "Sprite.h"
#include "Timer.h"
#include "Resources.h"
#include <sstream>
#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;
using std::stringstream;

// ------------------------------------------------------------------------------

using DistReal = uniform_real_distribution<float>;

enum SoundIds {MUSIC, POP};

// ------------------------------------------------------------------------------

class Balloons : public Game
{
private:
	Sprite * backg = nullptr;				// plano de fundo
	Sprite * popBox;						// caixa de placar
	Sprite * lostBox;						// caixa de placar
	Sprite * infoBar;						// caixa de informações

	Image * ball = nullptr;					// imagem do balão
	TileSet* tilesClick = nullptr;			// folha de sprite do click
	TileSet * tilesPop = nullptr;			// folha de sprite do estouro	
	
	Font * sysFont = nullptr;				// fonte do sistema
	Font * gameFont = nullptr;				// fonte do jogo

	DistReal randColor{ 0.0f, 1.0f };		// distribuição uniforme para cor
	DistReal randWidth{ 32.0f, 1247.0f };	// distribuição uniforme para largura (1280x800)
	DistReal randHeight{ 856.0f, 956.0f };	// distribuição uniforme para altura (1280x800)

	random_device rd;						// gerador aleatório não-determinístico
	mt19937 mt{rd()};						// gerador aleatório Mersenne Twister
	Timer timer;							// controle do tempo
	stringstream text;						// texto para exibição

	bool viewBBox = false;					// visualiza bounding box

	float posX = 0.0f;						// posição x do último balão
	float posY = 0.0f;						// posição y do último balão

public:
	static Scene * scene;					// cena do jogo
	static Audio * audio;					// sistema de áudio

	static uint popped;						// número de balões estourados
	static uint lost;						// número de balões perdidos
	
	void Init();							// inicializa jogo
	void Update();							// atualiza lógica do jogo
	void Draw();							// desenha jogo
	void Finalize();						// finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif