/**********************************************************************************
// Patterns (Arquivo de Cabeçalho)
// 
// Criação:     17 Out 2012
// Atualização: 10 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Aplicação de padrões e scripts em jogos
//
**********************************************************************************/

#ifndef _PATTERNS_H_
#define _PATTERNS_H_

// ------------------------------------------------------------------------------

enum { MUSIC, ALIEN1, ALIEN2, ALIEN3, ALIEN4, PLAYER, MISSILE };

// ------------------------------------------------------------------------------

#include "Game.h"                   // definição de um game
#include "Scene.h"                  // definição da cena do jogo
#include "Audio.h"                  // sistema de áudio
#include "Sprite.h"                 // desenho de sprites
#include "Resources.h"              // recursos utilizados no jogo
#include "Player.h"                 // definição do jogador
#include "Alien.h"                  // definção do inimigo
#include "Backg.h"                  // pano de fundo dinâmico
#include <sstream>                  // saída para strings
using std::stringstream;    

// ------------------------------------------------------------------------------

class Patterns : public Game
{
private:
    Instruction script[10] = {0};   // script de movimento
    bool viewBBox = false;          // visualiza bounding box
    stringstream text;              // texto temporário

public:
    static Audio * audio;           // gerenciador de áudio
    static Scene * scene;           // gerenciador de cena

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif