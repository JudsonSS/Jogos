/**********************************************************************************
// GravityGuy (Arquivo de Cabeçalho)
// 
// Criação:     05 Out 2011
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Jogo estilo plataforma usando a engine do curso
//
**********************************************************************************/

#ifndef _GRAVITYGUY_H_
#define _GRAVITYGUY_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

enum Sounds {MENU, MUSIC, TRANSITION};

// ------------------------------------------------------------------------------

class GravityGuy : public Game
{
private:
    static Game * level;            // nível atual do jogo

public:
    static Player * player;         // jogador 
    static Audio * audio;           // sistema de áudio
    static bool viewBBox;           // estado da bounding box

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    template<class T>
    static void NextLevel()         // muda para próximo nível do jogo
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};

// ---------------------------------------------------------------------------------

#endif