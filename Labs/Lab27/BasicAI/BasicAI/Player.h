/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:     10 Out 2012
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#ifndef _BASICAI_PLAYER_H_
#define _BASICAI_PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                     // objetos do jogo
#include "Sprite.h"                     // desenho de sprites
#include "Vector.h"                     // representação de vetores
#include "Particles.h"                  // sistema de partículas
#include "Controller.h"                 // entrada pelo controle
#include "Timer.h"                      // controle do tempo

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    Sprite * sprite;                    // sprite do objeto
    Particles * tail;                   // calda do jogador
    uint tailCount;                     // quantidade de partículas da calda
    
    Controller * gamepad;               // leitura do controle
    bool gamepadOn;                     // controle está ligado
    
    Timer timer;                        // controla tempo dos disparos
    llong start;                        // marcação de início do disparo
    bool axisCtrl;                      // habilita leitura de disparos
    bool keysCtrl;                      // habilita disparos pelas setas
    bool keysPressed;                   // qualquer seta pressionada
    float firingAngle;                  // direção dos disparos

public:
    static Image * missile;             // imagem do míssil
    Vector speed;                       // velocidade e direção de movimento

    Player();                           // construtor
    ~Player();                          // destrutor
    
    bool AxisTimed(int axisX, int axisY, float time);
    bool KeysTimed(bool pressed, float time);

    void Move(Vector && v);             // movimenta jogador
    void Update();                      // atualização
    void Draw();                        // desenho
}; 
// ---------------------------------------------------------------------------------

#endif