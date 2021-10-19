/**********************************************************************************
// Projectile (Arquivo de Cabeçalho)
// 
// Criação:     01 Out 2012
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Movimento de projétil
//
**********************************************************************************/

#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Font.h"
#include "Resources.h"
#include "Cannon.h"     
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

enum Sounds {CANNON, SPLASH};

// ------------------------------------------------------------------------------

class Projectile : public Game
{
private:
    Sprite * backg = nullptr;       // pano de fundo
    Sprite * base = nullptr;        // base do canhão
    Sprite * infoBox = nullptr;     // caixa de informações
    Sprite * keyMap = nullptr;      // caixa para teclas de atalho    
    Cannon * cannon = nullptr;      // canhão

    stringstream text;              // texto temporário

public:
    static Scene * scene;           // cena do jogo
    static Audio * audio;           // sistema de áudio
    static Font  * font;            // fonte para texto

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif