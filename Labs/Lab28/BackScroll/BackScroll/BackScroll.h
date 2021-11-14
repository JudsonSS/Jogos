/**********************************************************************************
// BackScroll (Arquivo de Cabeçalho)
// 
// Criação:     22 Out 2012
// Atualização: 12 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Desenhando e movimentando um background maior que a janela
//
**********************************************************************************/

#ifndef _BACKSCROLL_H_
#define _BACKSCROLL_H_

// ------------------------------------------------------------------------------

#include "Resources.h"              // recursos utilizados no jogo (cursor, ícone, etc.) 
#include "Game.h"                   // definição da classe jogo
#include "Font.h"                   // fonte para exibição de texto
#include "Sprite.h"                 // definição dos sprites
#include "Background.h"             // pano de fundo
#include <sstream>                  // saída para strings
using std::stringstream;    

// ------------------------------------------------------------------------------

class BackScroll : public Game
{
private:
    Sprite * infoBox;               // caixa de informações
    Sprite * keyMap;                // teclas de atalho
    Font   * font;                  // fonte normal
    Font   * bold;                  // fonte negrito
    stringstream text;              // texto temporário

    ViewPort viewport;              // área de visualização
    Background * backg;             // pano de fundo
    float scrollSpeed;              // velocidade de scrolling

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif