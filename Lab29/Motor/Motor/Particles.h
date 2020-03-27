/**********************************************************************************
// Particles (Arquivo de Cabeçalho)
// 
// Criação:		07 Out 2012
// Atualização:	12 Ago 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Define um sistema de partículas
//
**********************************************************************************/

#ifndef _DESENVJOGOS_PARTICLES_H_
#define _DESENVJOGOS_PARTICLES_H_

#ifdef MOTOR_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// ---------------------------------------------------------------------------------

#include "Sprite.h"											// desenho de sprites
#include "Timer.h"											// controle do tempo
#include "Types.h"											// tipos específicos da engine
#include "Vector.h"											// representação de vetores
#include <vector>											// vetores de elementos
#include <random>											// números aleatórios

// ---------------------------------------------------------------------------------

using std::vector;
using std::random_device;
using std::uniform_real_distribution;
using std::mt19937;
using Rnd = uniform_real_distribution<float>;

// ---------------------------------------------------------------------------------

struct DLL Emitter
{
	string imgFile;											// arquivo de imagem da partícula
	float  angle;											// direção do emissor de partículas
	float  spread;											// ângulo de espalhamento das partículas
	float  lifeTime;										// tempo de vida das partículas
	float  genTime;											// tempo entre geração de partículas
	float  percToDim;										// percentual de vida para começar a desaparecer
	float  minSpeed;										// velocidade mínima das partículas
	float  maxSpeed;										// velocidade máxima das partículas
	float  r, g, b, a;										// cor das partículas
};

struct Particle
{
	float  x, y;											// posição da partícula
	Vector speed;											// direção e velocidade
	llong  timeStamp;										// instante de criação
};

// ---------------------------------------------------------------------------------

class DLL Particles
{
private:
	Emitter emitter;										// emissor de partículas
	Sprite * sprite;										// sprite da partícula	
	vector<Particle*> particles;							// vetor de partículas

	Timer timer;											// controle de tempo
	
	random_device rd;										// gerador de semente
	mt19937 mt{ rd() };										// gerador de número aleatório
	Rnd randSpread { -emitter.spread, emitter.spread };		// valores aleatórios para o espalhamento
	Rnd randSpeed { emitter.minSpeed, emitter.maxSpeed };	// valores aleatórios para a velocidade

	void Build(float posX, float posY);						// cria uma partícula

public:
	Particles(const Emitter & desc);						// construtor
	~Particles();											// destrutor

	int  Size();											// retorna o número de partículas
	bool Inactive();										// retorna o estado das partículas
	Emitter& Generator();									// retorna ponteiro para o emissor
	void Generate(float x, float y, int amount = 1);		// gera novas partículas
	void Update(float delta);								// atualiza posição das partículas por delta
	void Draw(float z, float factor = 0.0f);				// desenha partículas		
}; 

// ---------------------------------------------------------------------------------

inline Emitter & Particles::Generator()
{ return emitter; }

inline int Particles::Size()
{ return particles.size(); }

inline bool Particles::Inactive()
{ return (particles.size() == 0); }

// ---------------------------------------------------------------------------------

#endif