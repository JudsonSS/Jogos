/**********************************************************************************
// Rock (Arquivo de Cabeçalho)
//
// Criação:		18 Mar 2013
// Atualização:	25 Jul 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Rocha espacial
//
**********************************************************************************/

#ifndef _ASTEROIDS_ROCK_H_
#define _ASTEROIDS_ROCK_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"						// tipos específicos da engine
#include "Object.h"						// interface de um objeto
#include "Animation.h"					// desenha animação
#include "TileSet.h"					// folha de sprites
#include "Vector.h"						// representação de vetores
#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

// ---------------------------------------------------------------------------------

class Rock : public Object
{
private:
	static TileSet * tile;				// tileset das rochas

	Animation * anim;					// animação da rocha
	Vector speed;						// velocidade da rocha
	uint frame;							// quadro da folha a ser utilizado
	float rAngle;						// incremento de ângulo em cada atualização 

	random_device rd;
	mt19937 mt { rd() };
	uniform_int_distribution<int> randFrame { 0, 3 };
	uniform_real_distribution<float> randAngle { 0.0f, 359.0f };
	uniform_real_distribution<float> randFactor { 0.0f, 10.0f };
	uniform_real_distribution<float> randWidth { 0.0f, float(window->Width()) };
	uniform_real_distribution<float> randHeight { 0.0f, float(window->Height()) };

public:
	static uint count;					// quantidade de rochas criadas

	Rock();								// construtor
	~Rock();							// destrutor

	void OnCollision(Object * obj);		// resolução da colisão
	void Update();						// atualização 
	void Draw();						// desenho
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Rock::Draw()
{ anim->Draw(frame, x, y, Layer::MIDDLE, scale, rotation); }

// ---------------------------------------------------------------------------------

#endif