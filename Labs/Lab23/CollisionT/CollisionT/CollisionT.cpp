/**********************************************************************************
// CollisionT (Código Fonte)
//
// Criação:     26 Jul 2019
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Teste de Colisão
//
**********************************************************************************/

#include "Engine.h"
#include "CollisionT.h"
#include "Shapes.h"
#include "Mouse.h"

// ------------------------------------------------------------------------------

Scene * CollisionT::scene = nullptr;            // cena do jogo
int CollisionT::index = 0;                      // índice do vetor

// ------------------------------------------------------------------------------

void CollisionT::Init()
{
    // cria fontes para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Tahoma14b.png");
    bold->Spacing("Resources/Tahoma14b.dat");

    // carrega pano de fundo e painel sobreposto 
    backg = new Sprite("Resources/Background.jpg");
    overlay = new Sprite("Resources/Overlay.png");

    // carrega folha de sprites e cria animação
    selSet = new TileSet("Resources/Select.png", 76, 32, 1, 3);
    select = new Animation(selSet, 0.250f, true);

    // cria objetos
    obj[0] = new Box();
    obj[1] = new Wheel();
    obj[2] = new Drop(); 
    obj[3] = new Plane(); 
    obj[4] = new Hammer(); 
    obj[5] = new Display(); 
    obj[6] = new Ball();
    obj[7] = new Dot();
    obj[8] = new Bolt(); 
    obj[9] = new House();

    // guarda posição inicial dos objetos
    pos[0] = { 226, 180 };
    pos[1] = { 426, 180 };
    pos[2] = { 576, 180 };
    pos[3] = { 726, 180 };
    pos[4] = { 926, 180 };
    pos[5] = { 226, 380 };
    pos[6] = { 426, 380 };
    pos[7] = { 576, 380 };
    pos[8] = { 726, 380 };
    pos[9] = { 926, 380 };

    // cria cena do jogo
    scene = new Scene();

    // adiciona objetos na cena
    for (const auto & elem : obj)
        scene->Add(elem, MOVING);

    // adiciona mouse na cena
    scene->Add(new Mouse(), MOVING);
}

// ------------------------------------------------------------------------------

void CollisionT::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // habilita/desabilita bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // deslocamento padrão
    float delta = 100 * gameTime;

    // desloca objeto selecionado
    if (window->KeyDown(VK_RIGHT))
        obj[index]->Translate(delta, 0);
    if (window->KeyDown(VK_LEFT))
        obj[index]->Translate(-delta, 0);
    if (window->KeyDown(VK_UP))
        obj[index]->Translate(0, -delta);
    if (window->KeyDown(VK_DOWN))
        obj[index]->Translate(0, delta);

    // altera escala e rotação do objeto
    if (window->KeyDown('S'))
        obj[index]->Scale(1 + 0.005f * delta);
    if (window->KeyDown('A'))
        obj[index]->Scale(1 - 0.005f * delta);
    if (window->KeyDown('Z'))
        obj[index]->Rotate(-0.5f * delta);
    if (window->KeyDown('X'))
        obj[index]->Rotate(0.5f * delta);

    // passa para o próximo objeto
    if (window->KeyPress(VK_TAB))
        index = (index + 1) % 10;

    // restaura objeto para seu estado inicial
    if (window->KeyPress('R'))
    {
        obj[index]->MoveTo(pos[index].x, pos[index].y);
        obj[index]->RotateTo(0);
        obj[index]->ScaleTo(1);
    }

    // atualiza animação da caixa de seleção
    select->NextFrame();

    // atualiza cena do jogo
    scene->Update();
    scene->CollisionDetection();
}

// ------------------------------------------------------------------------------

void CollisionT::Draw()
{
    // desenha pano de fundo e painel sobreposto
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    overlay->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);

    // desenha cena
    scene->Draw();

    // define cor dos textos
    Color textColor{ 0.65f, 0.65f, 0.65f, 1.0f };
    Color boldColor{ 0.55f, 0.55f, 0.55f, 1.0f };

    // desenha valores de posição, escala e rotação
    text.str("");
    text << "Escala: " << int(obj[index]->Scale() * 100) << "%";
    font->Draw(window->CenterX() - 155, 22.0f, text.str(), textColor);
    
    text.str("");
    text << "Posição: " << int(obj[index]->X()) << " x " << int(obj[index]->Y());
    font->Draw(window->CenterX() - 35, 22.0f, text.str(), textColor);

    text.str("");
    text << "Rotação: " << int(obj[index]->Rotation()) << "°";
    font->Draw(window->CenterX() + 110, 22.0f, text.str(), textColor);

    // desenha nomes dos objetos
    font->Draw(pos[0].x + 2, 260, "Caixa", textColor);
    font->Draw(pos[1].x + 3, 260, "Roda", textColor); 
    font->Draw(pos[2].x + 4, 260, "Gota", textColor); 
    font->Draw(pos[3].x + 2, 260, "Avião", textColor);
    font->Draw(pos[4].x - 4, 260, "Marreta", textColor);

    font->Draw(pos[5].x - 3, 460, "Monitor", textColor);
    font->Draw(pos[6].x + 5, 460, "Bola", textColor);
    font->Draw(pos[7].x + 1, 460, "Ponto", textColor);
    font->Draw(pos[8].x + 5, 460, "Raio", textColor);
    font->Draw(pos[9].x + 4, 460, "Casa", textColor);

    // desenha nome do objeto selecionado
    switch (index)
    {
    case BOX:     bold->Draw(window->CenterX() + 0, 49, "Caixa", boldColor);   break;
    case WHEEL:   bold->Draw(window->CenterX() + 1, 49, "Roda", boldColor);    break;
    case DROP:    bold->Draw(window->CenterX() + 2, 49, "Gota", boldColor);    break;
    case PLANE:   bold->Draw(window->CenterX() + 0, 49, "Avião", boldColor);   break;
    case HAMMER:  bold->Draw(window->CenterX() - 6, 49, "Marreta", boldColor); break;
    case DISPLAY: bold->Draw(window->CenterX() - 5, 49, "Monitor", boldColor); break;
    case BALL:    bold->Draw(window->CenterX() + 3, 49, "Bola", boldColor);    break;
    case DOT:     bold->Draw(window->CenterX() - 1, 49, "Ponto", boldColor);   break;
    case BOLT:    bold->Draw(window->CenterX() + 3, 49, "Raio", boldColor);    break;
    case HOUSE:   bold->Draw(window->CenterX() + 2, 49, "Casa", boldColor);    break;
    }

    // desenha mapeamento de teclas e suas funções
    float posY = window->Height() - 6.0f;
    font->Draw(window->CenterX() - 348.0f, posY, "Tab      Seleção", textColor);
    font->Draw(window->CenterX() - 235.0f, posY, "B      Bounding Box", textColor);
    font->Draw(window->CenterX() - 103.0f, posY, "R      Restaurar", textColor);
    font->Draw(window->CenterX() + 54.0f, posY, "Translação      Setas", textColor);
    font->Draw(window->CenterX() + 191.0f, posY, "Escala      A | S", textColor);
    font->Draw(window->CenterX() + 301.0f, posY, "Rotação      Z | X", textColor);

    //desenha posição do mouse
    text.str("");
    text << int(window->MouseX()) << " x " << int(window->MouseY());
    font->Draw(52, posY, text.str(), textColor);

    //desenha caixa de seleção animada
    select->Draw(pos[index].x, pos[index].y + 72);

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void CollisionT::Finalize()
{
    delete select;
    delete selSet;
    delete backg;
    delete overlay;
    delete scene;
    delete font;
    delete bold;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1152, 648);
    engine->window->Color(20, 20, 20);
    engine->window->Title("Teste de Colisão");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new CollisionT());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------


