/**********************************************************************************
// CollisionT (Arquivo de Cabeçalho)
//
// Criação:     26 Jul 2019
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Teste de Colisão
//
**********************************************************************************/

#ifndef _COLLISIONT_H_
#define _COLLISIONT_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Scene.h"
#include "Font.h"
#include "Resources.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

enum Objs { BOX, WHEEL, DROP, PLANE, HAMMER, DISPLAY, BALL, DOT, BOLT, HOUSE, MOUSE };

// ------------------------------------------------------------------------------

class CollisionT : public Game
{
private:
    Sprite * backg = nullptr;       // pano de fundo
    Sprite * overlay = nullptr;     // painel sobreposto

    TileSet * selSet = nullptr;     // folha de sprites da caixa de seleção
    Animation * select = nullptr;   // animação da caixa de seleção
    
    Font * font = nullptr;          // exibição de texto normal
    Font * bold = nullptr;          // exibição de texto negrito

    struct {
        float x;                    // coordenada x
        float y;                    // coordenada y
    } pos[10];                      // posição inicial dos objetos

    Object * obj[10] = {0};         // vetor de objetos

    bool viewBBox = false;          // visualização da bounding box
    stringstream text;              // conversão para texto    

public:
    static int index;               // índice do vetor
    static Scene * scene;           // cena do jogo

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif
