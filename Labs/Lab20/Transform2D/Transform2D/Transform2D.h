/**********************************************************************************
// Transform2D (Arquivo de Cabeçalho)
//
// Criação:     11 Nov 2011
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Teste de transformações - Translação, Rotação e Escala
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
    Controller * gamepad = nullptr;     // suporte a controle
    bool controllerOn = false;          // controle conectado

    Sprite * backg = nullptr;           // pano de fundo
    Sprite * infoBox = nullptr;         // caixa de informações
    Sprite * keyMap = nullptr;          // caixa para teclas de atalho
    Font * sysFont = nullptr;           // fonte do sistema

    Plane * plane = nullptr;            // objeto avião

    float backgScale = 0.0f;            // escala do pano de fundo
    stringstream text;                  // texto temporário

public:
    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ---------------------------------------------------------------------------------

#endif