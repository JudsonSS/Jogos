/**********************************************************************************
// Sound Control
//
// Criação:     14 Out 2011
// Atualização: 19 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Controla volume e freqüência do som
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Font.h"
#include "Audio.h"
#include "Sprite.h"
#include "Resources.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

enum Sounds { INTRO, PULSE, EXPLOSION };

// ------------------------------------------------------------------------------

class SoundCtrl : public Game
{
private:
    Audio * audio    = nullptr;     // sistema de áudio
    
    Font * titleFont = nullptr;     // fonte do título 
    Font * gameFont  = nullptr;     // fonte do jogo
    Font * sysFont   = nullptr;     // fonte padrão
    
    Sprite * bar     = nullptr;     // barra horizontal 
    Sprite * level   = nullptr;     // marcador de nível
    float volume     = 1.0f;        // volume da música
    float frequency  = 1.0f;        // freqüência da música

    bool  keyCtrl[2] = { 0 };       // controle de teclas
    stringstream text;              // texto para exibição

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ------------------------------------------------------------------------------

void SoundCtrl::Init()
{
    text << std::fixed;
    text.precision(3);

    audio = new Audio();
    audio->Add(INTRO, "Resources/Intro.wav");
    audio->Add(PULSE, "Resources/Pulse.wav", 3);
    audio->Add(EXPLOSION, "Resources/Explosion.wav", 3);

    titleFont = new Font("Resources/Bauhaus72.png");
    titleFont->Spacing("Resources/Bauhaus72.dat");

    gameFont = new Font("Resources/Tahoma16.png");
    gameFont->Spacing("Resources/Tahoma16.dat");

    sysFont = new Font("Resources/Tahoma10.png");
    sysFont->Spacing("Resources/Tahoma10.dat");

    bar = new Sprite("Resources/Bar.png");
    level = new Sprite("Resources/Level.png");

    keyCtrl[0] = false;
    keyCtrl[1] = false;

    // inicia tocando uma música 
    audio->Play(INTRO, true);
}

// ------------------------------------------------------------------------------

void SoundCtrl::Update()
{
    // sai com o pressionar do ESC
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

    // pressionamento das SETAS
    if (window->KeyDown(VK_UP))
    {
        volume += 0.5f * gameTime;

        if (volume > 2)
            volume = 2;
    }

    if (window->KeyDown(VK_DOWN))
    {
        volume -= 0.5f * gameTime;

        if (volume < 0)
            volume = 0;
    }

    if (window->KeyDown(VK_RIGHT))
    {
        frequency += 0.5f * gameTime;

        if (frequency > 2)
            frequency = 2;
    }

    if (window->KeyDown(VK_LEFT))
    {
        frequency -= 0.5f * gameTime;
        if (frequency < 0)
            frequency = 0;
    }

    if (window->KeyDown('R'))
    {
        volume = 1.0f;
        frequency = 1.0f;
    }

    audio->Frequency(INTRO, frequency);
    audio->Volume(INTRO, volume);
}

// ------------------------------------------------------------------------------

void SoundCtrl::Draw()
{
    titleFont->Draw(230, 80, "Sound Control", Color(0.9f, 0.9f, 0.0f, 1.0f), Layer::FRONT, 0.8f);

    gameFont->Draw(330, 170, "Background Music");
    sysFont->Draw(283, 220, "[DOWN]");
    sysFont->Draw(522, 220, "[UP]");

    text.str("");
    text << "Volume: " << volume;
    sysFont->Draw(370, 220, text.str());

    bar->Draw(window->CenterX(), 250);
    level->Draw(window->CenterX() - 134 + volume * 134, 250);

    text.str("");
    text << "Frequency: " << frequency;
    sysFont->Draw(360, 290, text.str());

    sysFont->Draw(283, 290, "[LEFT]"); 
    sysFont->Draw(500, 290, "[RIGHT]");

    bar->Draw(window->CenterX(), 320);
    level->Draw(window->CenterX() - 134 + frequency * 134, 320);

    gameFont->Draw(325, 390, "Laser Sound Effect");
    sysFont->Draw(375, 420, "[SPACE BAR]");

    gameFont->Draw(305, 470, "Explosion Sound Effect");
    sysFont->Draw(390, 500, "[ENTER]");

}

// ------------------------------------------------------------------------------

void SoundCtrl::Finalize()
{
    delete bar;
    delete level;
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
    engine->window->Title("Sound Ctrl");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    int status = engine->Start(new SoundCtrl());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

