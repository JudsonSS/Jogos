/**********************************************************************************
// Particles (Arquivo de Cabeçalho)
// 
// Criação:     07 Out 2012
// Atualização: 27 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define um sistema de partículas
//
**********************************************************************************/

#ifndef _PROGJOGOS_PARTICLES_H_
#define _PROGJOGOS_PARTICLES_H_

// ---------------------------------------------------------------------------------

#include "Sprite.h"                                             // desenho de sprites
#include "Timer.h"                                              // controle do tempo
#include "Types.h"                                              // tipos específicos da engine
#include "Vector.h"                                             // representação de vetores
#include <list>                                                 // lista de elementos
#include <random>                                               // números aleatórios

// ---------------------------------------------------------------------------------

using std::list;
using std::random_device;
using std::mt19937;
using Rnd = std::uniform_real_distribution<float>;

// ---------------------------------------------------------------------------------

struct Generator
{
    string imgFile;                                             // arquivo de imagem da partícula
    float  angle;                                               // direção do emissor de partículas
    float  spread;                                              // ângulo de espalhamento das partículas
    float  lifetime;                                            // tempo de vida das partículas (em segundos)
    float  frequency;                                           // frequência de geração de partículas (em segundos)
    float  percentToDim;                                        // percentual de vida para começar a desaparecer
    float  minSpeed;                                            // velocidade mínima das partículas
    float  maxSpeed;                                            // velocidade máxima das partículas
    Color  color;                                               // cor das partículas
};

struct Particle
{
    float  x, y;                                                // posição da partícula
    Vector speed;                                               // direção e velocidade
    llong  timestamp;                                           // instante de criação
};

// ---------------------------------------------------------------------------------

class Particles
{
private:
    Generator generator;                                        // gerador de partículas
    Sprite * sprite;                                            // sprite da partícula    
    list<Particle*> particles;                                  // lista de partículas

    Timer timer;                                                // controle de tempo
    random_device rd;                                           // gerador de semente
    mt19937 mt{ rd() };                                         // gerador de número aleatório
    Rnd RandSpread { -generator.spread/2, generator.spread/2 }; // valores aleatórios para o espalhamento
    Rnd RandSpeed { generator.minSpeed, generator.maxSpeed };   // valores aleatórios para a velocidade

    void Build(float posX, float posY);                         // cria uma partícula

public:
    Particles(const Generator & gen);                           // construtor
    ~Particles();                                               // destrutor

    uint Size();                                                // retorna o número de partículas
    bool Inactive();                                            // retorna o estado das partículas
    void Generate(float x, float y, int count = 1);             // gera novas partículas
    void Update(float delta);                                   // atualiza posição das partículas por delta
    void Draw(float z, float factor = 0.0f);                    // desenha partículas        
}; 

// ---------------------------------------------------------------------------------

inline uint Particles::Size()
{ return uint(particles.size()); }

inline bool Particles::Inactive()
{ return (particles.size() == 0); }

// ---------------------------------------------------------------------------------

#endif