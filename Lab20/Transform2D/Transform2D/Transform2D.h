/**********************************************************************************
// Transform2D (Arquivo de Cabeçalho)
//
// Criação:		11 Nov 2011
// Atualização:	15 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Teste de transformações - Translação, Rotação e Escala
//
**********************************************************************************/

#ifndef _TRANSFORM2D_H_
#define _TRANSFORM2D_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Font.h"
#include "Sprite.h"
#include "Controller.h"
#include "Resources.h"
#include "Plane.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

enum ButtonMapping { DPAD = 0, START = 7};

// ------------------------------------------------------------------------------

class Transform2D : public Game
{
private:
	Controller * gameCtrl = nullptr;	// entrada via controle
	Sprite * backg = nullptr;			// pano de fundo
	Sprite * infoBox = nullptr;			// caixa de informações
	Sprite * keyMap = nullptr;			// caixa para teclas de atalho
	Plane * plane = nullptr;			// objeto avião
	Font * sysFont = nullptr;			// fonte do sistema
	
	bool controllerOn = false;			// controle conectado
	float backgScale = 0.0f;			// escala do pano de fundo
	stringstream text;					// texto temporário

public:
	void Init();						// inicializa jogo
	void Update();						// atualiza lógica do jogo
	void Draw();						// desenha jogo
	void Finalize();					// finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif