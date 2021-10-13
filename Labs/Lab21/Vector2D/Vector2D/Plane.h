/**********************************************************************************
// Plane (Arquivo de Cabeçalho)
// 
// Criação:     24 Set 2012
// Atualização: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para um avião
//
**********************************************************************************/

#ifndef _VECTOR2D_PLANE_H_
#define _VECTOR2D_PLANE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                 // objetos do jogo 
#include "Sprite.h"                 // desenho de sprites
#include "Vector.h"                 // representação de vetor
#include "Types.h"                  // tipos específicos do motor
#include "Controller.h"             // leitura do controle
#include "Font.h"                   // exibição de texto
#include <sstream>                                
using std::stringstream;

// ------------------------------------------------------------------------------

enum ButtonMapping { SHOOT = 0, DPAD = 0, RESTART = 7 };

// ---------------------------------------------------------------------------------

class Plane : public Object
{
private:
    Controller * gamepad;           // entrada via controle
    bool gamepadOn;                 // controle conectado

    Sprite * sprite;                // sprite do avião
    Image * missile;                // imagem do míssil
    Vector direction;               // direção do avião

    Font * font;                    // fonte para exibição de texto
    stringstream text;              // buffer de texto

public:
    Plane();                        // construtor
    ~Plane();                       // destrutor

    int Width();                    // retorna largura do avião
    int Height();                   // retorna altura do avião
    float Angle();                  // retorna ângulo do vetor direção

    void Rotate(float angle);       // rotação (sobrescreve método)
    void Update();                  // atualização
    void Draw();                    // desenho
}; 

// ---------------------------------------------------------------------------------
// funções membro inline

inline int Plane::Width()
{ return sprite->Width(); }

inline int Plane::Height()
{ return sprite->Height(); }

inline float Plane::Angle()
{ return direction.angle; }

// ---------------------------------------------------------------------------------

#endif