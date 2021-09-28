/**********************************************************************************
// Platform (Arquivo de Cabeçalho)
// 
// Criação:     21 Abr 2012
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_PLATFORM_H_
#define _GRAVITYGUY_PLATFORM_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites

// ---------------------------------------------------------------------------------

enum PLATTYPES { SMALL, MEDIUM, LARGE, FINISH };

// ---------------------------------------------------------------------------------

class Platform : public Object
{
private:
    Sprite * platform = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma

public:
    Platform(float posX, float posY, 
             uint platType, 
             Color tint);                   // construtor    
    ~Platform();                            // destrutor

    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
}; 

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Platform::Draw()
{ platform->Draw(x, y, z, 1.0f, 0.0f, color); }

// ---------------------------------------------------------------------------------

#endif