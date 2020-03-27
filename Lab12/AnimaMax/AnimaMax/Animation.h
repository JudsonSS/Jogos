/**********************************************************************************
// Animation (Arquivo de Cabeçalho)
// 
// Criação:		28 Set 2011
// Atualização: 06 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Classe para animar seqüências em folha de sprites
//
**********************************************************************************/

#ifndef _DESENVJOGOS_ANIMATION_H_
#define _DESENVJOGOS_ANIMATION_H_

// ---------------------------------------------------------------------------------

#include "Sprite.h"					// tipo sprite para renderização
#include "TileSet.h"				// folha de sprites da animação
#include "Timer.h"					// tempo entre quadros da animação
#include "Types.h"					// tipos específicos da engine

// ---------------------------------------------------------------------------------

class Animation
{
private:
	uint  iniFrame;					// quadro inicial da seqüência
	uint  endFrame;					// quadro final da seqüência
	bool  animLoop;					// animação em loop infinito
	float animDelay;				// espaço de tempo entre quadros (em segundos)
	Timer timer;					// medidor de tempo entre quadros da animação
	TileSet * tileSet;				// ponteiro para folha de sprites da animação
	SpriteData sprite;				// sprite a ser desenhado

public:
	uint  frame;					// quadro atual da animação	

	// construtor
	Animation(TileSet * tiles, float delay, bool repeat);	

	// desenha o quadro atual da animação
	void Draw(float x, float y, float z = 0.5f);					

	// desenha um quadro da folha de sprites
	void Draw(uint animFrame, float x, float y, float z = 0.5f);	

	bool Inactive();				// verifica se a animação já encerrou
	void NextFrame();				// passa para o próximo frame da animação
	void Restart();					// reinicia a animacão (pelo primeiro frame da seqüência)
}; 

// ---------------------------------------------------------------------------------
// funções membro inline

// desenha quadro atual da animação
inline void Animation::Draw(float x, float y, float z)
{ Draw(frame, x, y, z); }

// verifica se a animação já encerrou
inline bool Animation::Inactive()
{ return !animLoop && (frame > endFrame || (frame == endFrame && timer.Elapsed(animDelay))); }

// reinicia a animacão (pelo primeiro frame da sequencia)
inline void Animation::Restart()
{ frame = 0; timer.Start(); }

// ---------------------------------------------------------------------------------

#endif