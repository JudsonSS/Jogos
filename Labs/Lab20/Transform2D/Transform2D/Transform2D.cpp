/**********************************************************************************
// Transform2D (Código Fonte)
//
// Criação:     11 Nov 2011
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Teste de transformações - Translação, Rotação e Escala
//
**********************************************************************************/

#include "Engine.h"
#include "Transform2D.h"

// ------------------------------------------------------------------------------

void Transform2D::Init()
{
    // inicializa controle
    gamepad = new Controller();
    controllerOn = gamepad->Initialize();

    // cria fontes para exibição de texto
    sysFont = new Font("Resources/Tahoma14.png");
    sysFont->Spacing("Resources/Tahoma14.dat");

    // carrega painéis e pano de fundo
    backg = new Sprite("Resources/Kamikaze.jpg");
    infoBox = new Sprite("Resources/InfoBox.png");
    keyMap = new Sprite("Resources/KeyMap.png");
    
    // cria objeto avião
    plane = new Plane();
    plane->MoveTo(window->CenterX(), window->CenterY());

    // calcula proporção entre a janela e o pano de fundo
    float horzScale = window->Width() / 1920.0f;
    float vertScale = window->Height() / 1080.0f;

    // define escala para o pano de fundo
    backgScale = horzScale > vertScale ? horzScale : vertScale;
}

// ------------------------------------------------------------------------------

void Transform2D::Update()
{
    // sai com pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // deslocamento padrão
    float delta = 250 * gameTime;

    // -----------------
    // Teclado
    // -----------------
    if (window->KeyDown(VK_RIGHT))
        plane->Translate(delta, 0);

    if (window->KeyDown(VK_LEFT))
        plane->Translate(-delta, 0);

    if (window->KeyDown(VK_UP))
        plane->Translate(0, -delta);

    if (window->KeyDown(VK_DOWN))
        plane->Translate(0, delta);

    if (window->KeyDown('S'))
        plane->Scale(1 + 0.005f * delta);

    if (window->KeyDown('A'))
        plane->Scale(1 - 0.005f * delta);

    if (window->KeyDown('Z'))
        plane->Rotate(-0.5f * delta);

    if (window->KeyDown('X'))
        plane->Rotate(0.5f * delta);

    if (window->KeyDown('R'))
    {
        plane->MoveTo(window->CenterX(), window->CenterY());
        plane->RotateTo(0);
        plane->ScaleTo(1);
    }

    // -----------------
    // Controle
    // -----------------

    if (controllerOn)
    {
        gamepad->UpdateState();

        plane->Translate(gamepad->Axis(AxisX) * gameTime, gamepad->Axis(AxisY) * gameTime);
        plane->Scale(1 - gamepad->Axis(AxisZ) * 0.001f * gameTime);
        plane->Rotate(delta * gamepad->Axis(AxisRX) * 0.001f);
        plane->Rotate(-delta * gamepad->Axis(AxisRY) * 0.001f);

        if (gamepad->ButtonPress(START))
        {
            plane->MoveTo(window->CenterX(), window->CenterY());
            plane->RotateTo(0);
            plane->ScaleTo(1);
        }

        switch (gamepad->Dpad(DPAD))
        {
        case 0:
            plane->Translate(0.0f, -delta);    // para cima
            break;
        case 4500:
            plane->Translate(delta, -delta);   // para cima e direita
            break;
        case 9000:
            plane->Translate(delta, 0.0f);     // para direita
            break;
        case 13500:
            plane->Translate(delta, delta);    // para baixo e direita
            break;
        case 18000:
            plane->Translate(0.0f, delta);     // para baixo
            break;
        case 22500:
            plane->Translate(-delta, delta);   // para baixo e esquerda
            break;
        case 27000:
            plane->Translate(-delta, 0.0f);   // para esquerda
            break;
        case 31500:
            plane->Translate(-delta, -delta);  // para cima e esquerda
            break;
        }
    }
} 

// ------------------------------------------------------------------------------

void Transform2D::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, backgScale);
    keyMap->Draw(window->CenterX(), window->Height() - 16.0f, Layer::UPPER);
    infoBox->Draw(120, 100, Layer::UPPER);
    plane->Draw();

    Color textColor { 0.65f, 0.65f, 0.65f, 1.0f };

    text.str("");
    text << "Transformações 2D";
    sysFont->Draw(45, 64, text.str(), textColor);

    text.str("");
    text << "Posição do avião: " << int(plane->X()) << " x " << int(plane->Y());
    sysFont->Draw(45, 104, text.str(), textColor);

    text.str("");
    text << "Tamanho do avião: " << int(plane->Width() * plane->Scale()) << " x " << int(plane->Height() * plane->Scale());
    sysFont->Draw(45, 124, text.str(), textColor);

    text.str("");
    text << "Ângulo de rotação: " << int(plane->Rotation());
    sysFont->Draw(45, 144, text.str(), textColor);

    if (controllerOn)
    {
        text.str("");
        text << "LT | RT    Escala         LStick     Translação          Rotação      RStick      Reiniciar      Start";
        sysFont->Draw(window->CenterX() - 234.0f, window->Height() - 6.0f, text.str(), textColor);
    }
    else
    {
        text.str("");
        text << "A | S      Escala         Setas     Translação           Rotação      Z | X       Reiniciar        R";
        sysFont->Draw(window->CenterX() - 228.0f, window->Height() - 6.0f, text.str(), textColor);
    }
} 

// ------------------------------------------------------------------------------

void Transform2D::Finalize()
{
    delete backg;
    delete keyMap;
    delete infoBox;
    delete plane;
    delete gamepad;
    delete sysFont;
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
    engine->window->Size(1200, 640);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Transform 2D");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Transform2D());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

