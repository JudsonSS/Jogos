/**********************************************************************************
// FlyDemo (Arquivo de Cabeçalho)
// 
// Criação:		10 Out 2012
// Atualização:	06 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Demonstração da inteligência artificial de uma mosca
//
**********************************************************************************/

#ifndef _FLYDEMO_H_
#define _FLYDEMO_H_

// ------------------------------------------------------------------------------

#include "Game.h"						// definição da classe jogo
#include "Sprite.h"						// desenho de sprites
#include "Scene.h"						// gerenciamento da cena
#include "Resources.h"					// recursos utilizados no jogo

// ------------------------------------------------------------------------------

enum { TRASHCAN, FLY, MOUSE };			// identificadores dos objetos

// ------------------------------------------------------------------------------

class FlyDemo : public Game
{
private:
	Sprite * backg = nullptr;			// pano de fundo	
	bool viewBBox = false;				// exibe bounding box

public:
	static Scene * scene;				// gerenciador de cena

	void Init();						// inicialização
	void Update();						// atualização
	void Draw();						// desenho
	void Finalize();					// finalização
};

// ---------------------------------------------------------------------------------

#endif