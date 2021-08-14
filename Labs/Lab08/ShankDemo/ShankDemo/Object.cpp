/**********************************************************************************
// Object (Código Fonte)
//
// Criação:     01 Out 2007
// Atualização: 14 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Essa é a classe base para todos objetos do jogo.
//
//              Um objeto do jogo é qualquer coisa que possámos querer desenhar
//              ou interagir dentro do jogo. Por exemplo, um soldado, um prédio,
//              um projétil, uma forma geométrica, etc.
//
**********************************************************************************/

#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

Window* & Object::window   = Engine::window;           // ponteiro para a janela
float   & Object::gameTime = Engine::frameTime;        // tempo do último quadro

// -------------------------------------------------------------------------------

Object::Object() : x(0.0f), y(0.0f), z(0.5f)
{
}

// -------------------------------------------------------------------------------

Object::~Object()
{
}

// -------------------------------------------------------------------------------