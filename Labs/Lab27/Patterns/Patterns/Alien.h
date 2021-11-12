/**********************************************************************************
// Alien (Arquivo de Cabeçalho)
// 
// Criação:     25 Mar 2013
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Executa scripts com padrões de movimentação
//
**********************************************************************************/

#ifndef _PATTERNS_ALIEN_H_
#define _PATTERNS_ALIEN_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Vector.h"
#include "Timer.h"
#include "Player.h"
#include "Random.h"

// --------------------------------------------------------------------------------

struct Instruction
{
    int instruction;
    float angle;
    float magnitude;
    float duration;
};

// MOVE      | Ângulo    | Magnitude | Duração
// MOVETO    | PosX      | PosY      | Magnitude
// SLIDE     | Ângulo    | Magnitude | Duração
// SLIDETO   | PosX      | PosY      | Magnitude
// TURN      | Ângulo    | Magnitude | Duração
// ROTATE    | Ângulo    | Magnitude | Duração
// RANDOM    | -         | -         | Duração
// JUMP      | Instrução | -         | -

enum InstructionTypes 
{
    MOVE,           // move em uma direção e velocidade por um tempo
    MOVETO,         // move para uma posição x, y
    SLIDE,          // o mesmo que MOVE, porém sem rotacionar
    SLIDETO,        // o mesmo que MOVETO, porém sem rotacionar
    TURN,           // indica a direção que o objeto deve seguir
    ROTATE,         // rotaciona a direção do objeto por um tempo
    RANDOM,         // move em uma direção aleatória por um tempo
    JUMP            // pula para uma instrução podendo fazer um loop
};

// ---------------------------------------------------------------------------------

class Alien : public Object
{
private:
    TileSet * alienSet;                 // tileset do objeto
    Animation * anim;                   // animação do objeto
    Vector speed;                       // velocidade e direção
    
    Instruction * script;               // vetor de instruções
    int index;                          // índice da instrução atual
    int end;                            // índice da última instrução
    float duration;                     // duração da instrução atual
    
    Timer timer;                        // timer para instruções
    RandF angle;                        // valor aleatório para ângulo
    RandF magnitude;                    // valor aleatório para magnitude
    
public:
    Alien(uint alien, Instruction * vet, int tam, float pX, float pY);    
    ~Alien();
    
    void OnCollision(Object * obj);     // resolução da colisão
    void Update();                      // atualização
    void Draw();                        // desenho
}; 

// ---------------------------------------------------------------------------------

inline void Alien::Draw()
{ anim->Draw(x, y, Layer::MIDDLE, scale, rotation ); }

// ---------------------------------------------------------------------------------


#endif