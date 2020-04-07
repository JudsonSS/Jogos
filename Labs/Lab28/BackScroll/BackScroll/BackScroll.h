/**********************************************************************************
// BackScroll (Arquivo de Cabeçalho)
// 
// Criação:		22 Out 2012
// Atualização:	14 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Desenhando e movimentando um background maior que a janela
//
**********************************************************************************/

#ifndef _BACKSCROLL_H_
#define _BACKSCROLL_H_

// ------------------------------------------------------------------------------

#include "Resources.h"				// recursos utilizados no jogo (cursor, ícone, etc.) 
#include "Game.h"					// definição da classe jogo
#include "Font.h"					// fonte para exibição de texto
#include "Sprite.h"					// definição dos sprites
#include <sstream>					// saída para strings
using std::stringstream;	

// ------------------------------------------------------------------------------

class BackScroll : public Game
{
private:
	Sprite * infoBox;				// caixa de informações
	Sprite * keyMap;				// caixa para teclas de atalho
	Font   * font;					// fonte para texto normal
	Font   * bold;					// fonte para texto negrito
	stringstream text;				// texto temporário

	ViewPort viewport;				// viewport do jogo
	Sprite * backg;					// pano de fundo com scrolling
	float maxWidth;					// largura máxima do background
	float maxHeight;				// altura máxima do background
	float scrollSpeed;				// velocidade de scrolling

public:
	void Init();					// inicializa jogo
	void Update();					// atualiza lógica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif