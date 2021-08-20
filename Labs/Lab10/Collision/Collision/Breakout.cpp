/**********************************************************************************
// Breakout (Código Fonte)
// 
// Criação:     26 Mar 2012
// Atualização: 20 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Uso da classe Scene para gerenciar objetos e tratar colisão
//
**********************************************************************************/

#include "Engine.h"
#include "Breakout.h"
#include "Resources.h"
#include "Player.h"
#include "Block.h"
#include "Ball.h"

// ------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Scene * Breakout::scene = nullptr;

// ------------------------------------------------------------------------------

void Breakout::Init()
{
    // cena do jogo
    scene = new Scene();

    // carrega background
    backg = new Sprite("Resources/Background.jpg");

    // carregar imagens
    tile1 = new Image("Resources/Tile1.png");
    tile2 = new Image("Resources/Tile2.png");
    tile3 = new Image("Resources/Tile3.png");
    tile4 = new Image("Resources/Tile4.png");
    tile5 = new Image("Resources/Tile5.png");
    
    // ---------------------------
    // cria jogador
    Player * player = new Player();
    scene->Add(player, MOVING);

    // ---------------------------
    // cria bola

    Ball * ball = new Ball(player);
    scene->Add(ball, MOVING);

    // -----------------------------------------
    // posição dos blocos

    float line1 = 50.0f;
    float line2 = 80.0f;
    float line3 = 110.0f;
    float line4 = 140.0f;
    float line5 = 170.0f;

    // -----------------------------------------
    // linha 1 de blocos    

    Block* block;
    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 350.0f, line1);
    scene->Add(block, STATIC);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 270.0f, line1);
    scene->Add(block, STATIC);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 190.0f, line1);
    scene->Add(block, STATIC);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 110.0f, line1);
    scene->Add(block, STATIC);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 30.0f, line1);
    scene->Add(block, STATIC);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() + 50.0f, line1);
    scene->Add(block, STATIC);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() + 130.0f, line1);
    scene->Add(block, STATIC);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() + 210.0f, line1);
    scene->Add(block, STATIC);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() + 290.0f, line1);
    scene->Add(block, STATIC);

    // -----------------------------------------
    // linha 2 de blocos    

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 350.0f, line2);
    scene->Add(block, STATIC);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 270.0f, line2);
    scene->Add(block, STATIC);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 190.0f, line2);
    scene->Add(block, STATIC);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 110.0f, line2);
    scene->Add(block, STATIC);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 30.0f, line2);
    scene->Add(block, STATIC);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() + 50.0f, line2);
    scene->Add(block, STATIC);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() + 130.0f, line2);
    scene->Add(block, STATIC);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() + 210.0f, line2);
    scene->Add(block, STATIC);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() + 290.0f, line2);
    scene->Add(block, STATIC);

    // -----------------------------------------
    // linha 3 de blocos    

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 350.0f, line3);
    scene->Add(block, STATIC);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 270.0f, line3);
    scene->Add(block, STATIC);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 190.0f, line3);
    scene->Add(block, STATIC);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 110.0f, line3);
    scene->Add(block, STATIC);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 30.0f, line3);
    scene->Add(block, STATIC);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() + 50.0f, line3);
    scene->Add(block, STATIC);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() + 130.0f, line3);
    scene->Add(block, STATIC);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() + 210.0f, line3);
    scene->Add(block, STATIC);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() + 290.0f, line3);
    scene->Add(block, STATIC);

    // -----------------------------------------
    // linha 4 de blocos    

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 350.0f, line4);
    scene->Add(block, STATIC);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 270.0f, line4);
    scene->Add(block, STATIC);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 190.0f, line4);
    scene->Add(block, STATIC);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 110.0f, line4);
    scene->Add(block, STATIC);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 30.0f, line4);
    scene->Add(block, STATIC);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() + 50.0f, line4);
    scene->Add(block, STATIC);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() + 130.0f, line4);
    scene->Add(block, STATIC);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() + 210.0f, line4);
    scene->Add(block, STATIC);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() + 290.0f, line4);
    scene->Add(block, STATIC);

    // -----------------------------------------
    // linha 5 de blocos    

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 350.0f, line5);
    scene->Add(block, STATIC);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 270.0f, line5);
    scene->Add(block, STATIC);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 190.0f, line5);
    scene->Add(block, STATIC);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 110.0f, line5);
    scene->Add(block, STATIC);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 30.0f, line5);
    scene->Add(block, STATIC);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() + 50.0f, line5);
    scene->Add(block, STATIC);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() + 130.0f, line5);
    scene->Add(block, STATIC);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() + 210.0f, line5);
    scene->Add(block, STATIC);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() + 290.0f, line5);
    scene->Add(block, STATIC);
}

// ------------------------------------------------------------------------------

void Breakout::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();
    
    // habilita/desabilita visualização de sprites
    if (ctrlKeyS && window->KeyDown('S'))
    {
        viewScene = !viewScene;
        ctrlKeyS = false;
    }
    else if (window->KeyUp('S'))
    {
        ctrlKeyS = true;
    }    

    // habilita/desabilita visualização da bounding box
    if (ctrlKeyB && window->KeyDown('B'))
    {
        viewBBox = !viewBBox;
        ctrlKeyB = false;
    }
    else if (window->KeyUp('B'))
    {
        ctrlKeyB = true;
    }

    // atualiza objetos da cena
    scene->Update();

    // detecção e resolução de colisão
    scene->CollisionDetection();
} 

// ------------------------------------------------------------------------------

void Breakout::Draw()
{
    // desenha a cena
    if (viewScene)
    {
        backg->Draw(0.0f, 0.0f, Layer::BACK);
        scene->Draw();
    }

    // desenha a bounding box de todos os objetos
    if (viewBBox)
    {
        scene->DrawBBox();
    }
} 

// ------------------------------------------------------------------------------

void Breakout::Finalize()
{
    // apaga sprite
    delete backg;

    // apaga imagens
    delete tile1;
    delete tile2;
    delete tile3;
    delete tile4;
    delete tile5;

    delete scene;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura a janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Breakout");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);
    
    // inicia jogo
    int status = engine->Start(new Breakout());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

