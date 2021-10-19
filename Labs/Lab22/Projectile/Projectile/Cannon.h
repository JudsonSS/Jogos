/**********************************************************************************
// Cannon (Arquivo de Cabeçalho)
// 
// Criação:     01 Out 2012
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define o canhão do jogo
//
**********************************************************************************/

#ifndef _PROJECTILE_CANNON_H_
#define _PROJECTILE_CANNON_H_

// ---------------------------------------------------------------------------------

#include "Vector.h"                             // representação de vetor
#include "Object.h"                             // representação de objetos 
#include "Sprite.h"                             // desenho de sprites
#include "Controller.h"                         // leitura do controle
#include "Types.h"                              // tipos específicos da engine
#include "Timer.h"                              // medição de tempo

// ---------------------------------------------------------------------------------

enum ButtonMapping { SHOOT = 0, NONSTOP = 1, AIR = 6 };

// ---------------------------------------------------------------------------------

class Cannon : public Object
{
private:
    Sprite * sprite;                            // sprite do canhão
    Controller * gamepad;                       // entrada por controle
    bool gamepadOn;                             // controle conectado

    Timer timer;                                // medidor de tempo
    llong start;                                // marcação de início do tempo
    bool keyCtrl;                               // estado de liberação da tecla
    bool buttonCtrl;                            // estado de liberação do botão
    
public:
    Vector direction;                           // direção do canhão

    Cannon();                                   // construtor
    ~Cannon();                                  // destrutor

    bool KeyTimed(int vkcode, float time);      // controle de pressionamento por tempo 
    bool ButtonTimed(int button, float time);   // controle de pressionamento por tempo 
    
    void Rotate(float angle);                   // sobrescreve rotação
    void Update();                              // atualização
    void Draw();                                // desenho
}; 

// ---------------------------------------------------------------------------------

#endif