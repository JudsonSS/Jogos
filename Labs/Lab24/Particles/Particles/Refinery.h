/**********************************************************************************
// Refinery (Arquivo de Cabeçalho)
//
// Criação:     07 Out 2012
// Atualização: 27 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Demonstração do sistema de partículas
//
**********************************************************************************/

#ifndef _REFINERY_H_
#define _REFINERY_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "Audio.h"
#include "Scene.h"
#include "Font.h"
#include "Resources.h"         
#include "Smoke.h"
#include "Fireworks.h"
#include <sstream>
#include <random>

// ---------------------------------------------------------------------------------

using std::stringstream;
using std::random_device;
using std::uniform_real_distribution;
using std::mt19937;
using Rnd = uniform_real_distribution<float>;

// ------------------------------------------------------------------------------

enum ObjectTypes  { SMOKE, FIREWORKS };
enum SoundIds { MACHINERY };

// ------------------------------------------------------------------------------

class Refinery : public Game
{
private:
    Sprite * backg = nullptr;       // pano de fundo
    Sprite * overlay = nullptr;     // moldura da interface
    Sprite * onoff = nullptr;       // indicação de ligado/desligado
    Smoke  * exhausts[4] = {0};     // exaustores de fumaça
    Font   * font = nullptr;        // fonte normal
    Font   * bold = nullptr;        // fonte negrito

    bool smokeOn = false;           // estado da refinaria
    bool nightOn = false;           // estado da iluminação

    stringstream text;              // texto temporário
    random_device rd;               // gerador aleatório para a semente
    mt19937 mt { rd() };            // gerador pseudoaleatório de números
    Rnd smokeAng { 30, 150 };       // faixa de valores aleatórios para o ângulo

public:
    static Audio * audio;           // sistema de áudio
    static Scene * scene;           // cena do jogo

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif