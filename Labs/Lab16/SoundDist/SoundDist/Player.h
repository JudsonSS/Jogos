/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:     07 Fev 2013
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Player usado em SoundDistance
//
**********************************************************************************/

#ifndef _SOUNDDIST_PLAYER_H_
#define _SOUNDDIST_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"          // tipos específicos da engine
#include "Object.h"         // interface de object
#include "Sprite.h"         // interface de sprites

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    Sprite  * sprite;       // sprite do player
    Image   * missile;      // imagem do míssil
    TileSet * explo;        // quadros da explosão
    float vel;              // velocidade horizontal do player
    bool keyCtrl;           // controla pressionamento de tecla

public:
    Player();               // construtor
    ~Player();              // destrutor

    void Update();          // atualização
    void Draw();            // desenho
};

// ---------------------------------------------------------------------------------

inline void Player::Draw()
{ sprite->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif