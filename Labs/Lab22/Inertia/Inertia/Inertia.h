/**********************************************************************************
// Inertia (Arquivo de Cabeçalho)
// 
// Criação:     14 Mar 2013
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Movimentação por aplicação de um vetor Força
//
**********************************************************************************/

#ifndef _INERTIA_H_
#define _INERTIA_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Font.h"
#include "Resources.h"
#include "Ship.h"    
#include "Missile.h" 
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

enum Sounds {JETUP, LOOPUP, JETDOWN, LOOPDOWN, FIRE, EXPLOSION};

// ------------------------------------------------------------------------------

class Inertia : public Game
{
private:
    Sprite * backg = nullptr;        // pano de fundo
    Sprite * keyMap = nullptr;      // caixa para teclas de atalho    
    Ship   * ship = nullptr;        // nave espacial
    Font   * font = nullptr;        // exibição de texto
    Font   * bold = nullptr;        // exibição de texto
    stringstream text;              // geração de texto

public:
    static TileSet * exploSet;      // tileset da explosão
    static Scene * scene;           // cena do jogo
    static Audio * audio;           // sistema de áudio

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif