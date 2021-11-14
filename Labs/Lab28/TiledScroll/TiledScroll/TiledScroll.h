/**********************************************************************************
// TiledScroll (Arquivo de Cabeçalho)
//
// Criação:     22 Out 2012
// Atualização: 12 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Desenhando e movimentando um background formado por blocos
//
**********************************************************************************/

#ifndef _TILEDSCROLL_H_
#define _TILEDSCROLL_H_

// ------------------------------------------------------------------------------

#include "Resources.h"              // recursos utilizados no jogo (cursor, ícone, etc.) 
#include "Game.h"                   // definição da classe jogo
#include "Font.h"                   // fonte para exibição de texto
#include "Sprite.h"                 // definição dos sprites
#include "Background.h"             // pano de fundo
#include <sstream>                  // saída para strings
using std::stringstream;    

// ------------------------------------------------------------------------------

class TiledScroll : public Game
{
private:
    Sprite * infoBox = nullptr;     // caixa de informações
    Sprite * keyMap = nullptr;      // caixa para teclas de atalho
    Font * font = nullptr;          // fonte para texto normal
    Font * bold = nullptr;          // fonte para texto negrito
    stringstream text;              // texto temporário

    Image * tiles = nullptr;        // imagem formada por blocos
    Background * backg = nullptr;   // pano de fundo
    ViewPort viewport;              // área de visualização
    float scrollSpeed;              // velocidade de scrolling

public:
    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif