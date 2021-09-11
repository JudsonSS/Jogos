/**********************************************************************************
// Sound Demo
//
// Criação:     14 Out 2011
// Atualização: 11 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de uso da classe Sound e Audio
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Font.h"
#include "Audio.h"
#include "Resources.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

enum Sounds { INTRO, PULSE, EXPLOSION };

// ------------------------------------------------------------------------------

class SoundDemo : public Game
{
private:
    Audio * audio     = nullptr;    // sistema de áudio
    Font  * titleFont = nullptr;    // fonte do título 
    Font  * gameFont  = nullptr;    // fonte do jogo
    Font  * sysFont   = nullptr;    // fonte padrão

    bool  keyCtrl[2] = { 0 };       // controle de teclas

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};


// ------------------------------------------------------------------------------


void SoundDemo::Init()
{
    audio = new Audio();
    audio->Add(INTRO, "Resources/Intro.wav");
    audio->Add(PULSE, "Resources/Pulse.wav");
    audio->Add(EXPLOSION, "Resources/Explosion.wav");

    titleFont = new Font("Resources/Bauhaus72.png");
    titleFont->Spacing("Resources/Bauhaus72.dat");

    gameFont = new Font("Resources/Tahoma16.png");
    gameFont->Spacing("Resources/Tahoma16.dat");

    sysFont = new Font("Resources/Tahoma10.png");
    sysFont->Spacing("Resources/Tahoma10.dat");

    keyCtrl[0] = false;
    keyCtrl[1] = false;

    // inicia tocando uma música 
    audio->Play(INTRO);
}

// ------------------------------------------------------------------------------

void SoundDemo::Update()
{
    // sai com pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
    window->Close();

    // pressionamento da BARRA DE ESPAÇOS
    if (keyCtrl[0] && window->KeyDown(VK_SPACE))
    {
        audio->Play(PULSE);
        keyCtrl[0] = false;
    }
    else if (window->KeyUp(VK_SPACE))
    {
        keyCtrl[0] = true;
    }

    // pressionamento do ENTER
    if (keyCtrl[1] && window->KeyDown(VK_RETURN))
    {
        audio->Play(EXPLOSION);
        keyCtrl[1] = false;
    }
    else if (window->KeyUp(VK_RETURN))
    {
        keyCtrl[1] = true;
    }
}

// ------------------------------------------------------------------------------

void SoundDemo::Draw()
{
    titleFont->Draw(225, 150, "Sound Demo", Color(0.9f, 0.9f, 0.0f, 1.0f));

    gameFont->Draw(325, 370, "Laser Sound Effect");
    sysFont->Draw(375, 400, "[SPACE BAR]");

    gameFont->Draw(305, 450, "Explosion Sound Effect");
    sysFont->Draw(390, 480, "[ENTER]");

}

// ------------------------------------------------------------------------------

void SoundDemo::Finalize()
{
    delete gameFont;
    delete titleFont;
    delete sysFont;
    delete audio;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura motor 
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 600);
    engine->window->Color(25, 50, 150);
    engine->window->Title("Sound Demo");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    int status = engine->Start(new SoundDemo());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

