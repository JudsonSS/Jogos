/**********************************************************************************
// Animation (Código Fonte)
// 
// Criação:		28 Set 2011
// Atualização: 06 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Classe para animar seqüências em folha de sprites
//
**********************************************************************************/

#include "Engine.h"
#include "Animation.h"
#include "Renderer.h"

// ---------------------------------------------------------------------------------

Animation::Animation(TileSet * tiles, float delay, bool repeat) : 
	tileSet(tiles), 
	animDelay(delay), 
	animLoop(repeat)
{
	// sempre inicia a animação pelo primeiro quadro
	frame = iniFrame = 0;

	// o último quadro é sempre um a menos que o número de quadros
	endFrame = tileSet->Size() - 1;

	// configura sprite
	sprite.scale     = 1.0f;
	sprite.rotation  = 0.0f;
	sprite.width     = tileSet->TileWidth();
	sprite.height    = tileSet->TileHeight();
	sprite.texSize.x = float(tileSet->TileWidth())  / tileSet->Width();
	sprite.texSize.y = float(tileSet->TileHeight()) / tileSet->Height();
	sprite.texture   = tileSet->View();
	
	// animação iniciada (começa a contar o tempo)
	timer.Start();				
}

// ---------------------------------------------------------------------------------

void Animation::NextFrame()
{
	// passa para o próximo quadro após espaço de tempo estipulado em animDelay
	if (timer.Elapsed(animDelay))
	{
		frame++;

		// volta para o primeiro quadro se estiver usando o modo ENDLESS
		if (animLoop && frame > endFrame)
			frame = 0;

		// frame iniciado (começa a contar o tempo)
		timer.Start();		
	}
}

// ---------------------------------------------------------------------------------

void Animation::Draw(uint animFrame, float x, float y, float z)
{
	// configura dados básicos
	sprite.x = x;
	sprite.y = y;
	sprite.depth = z;

	// configura coordenadas da textura do sprite
	sprite.texCoord.x = (animFrame % tileSet->Columns()) * sprite.texSize.x;
	sprite.texCoord.y = (animFrame / tileSet->Columns()) * sprite.texSize.y;

	// adiciona o sprite na lista de desenho
	Engine::renderer->Draw(&sprite);
}

// --------------------------------------------------------------------------------