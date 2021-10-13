/**********************************************************************************
// Plane (Código Fonte)
// 
// Criação:     24 Set 2012
// Atualização: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para um avião
//
**********************************************************************************/

#include "Plane.h"
#include "Missile.h"
#include "Vector2D.h"

// ---------------------------------------------------------------------------------

Plane::Plane()
{
    // inicializa controle
    gamepad = new Controller();
    gamepadOn = gamepad->Initialize();

    // cria sprite
    sprite = new Sprite("Resources/Airplane.png");
    missile = new Image("Resources/Missile.png");

    // cria fontes para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");

    // posição, escala e rotação inicial do avião
    MoveTo(window->CenterX(), window->CenterY());
    RotateTo(0);
    ScaleTo(0.5f);

    // direção inicial do avião
    direction.angle = 90.0f;
    direction.magnitude = 1.0f;
}

// ---------------------------------------------------------------------------------

Plane::~Plane()
{
    delete font;
    delete missile;
    delete sprite;
    delete gamepad;
}
// -------------------------------------------------------------------------------

void Plane::Rotate(float angle)
{
    Object::Rotate(angle);
    direction.Rotate(angle);
}

// -------------------------------------------------------------------------------

void Plane::Update()
{
    // deslocamento padrão
    float delta = 250 * gameTime;

    // -----------------
    // Teclado
    // -----------------

    // movimenta com as setas
    if (window->KeyDown(VK_RIGHT))
        Translate(delta, 0);
    if (window->KeyDown(VK_LEFT))
        Translate(-delta, 0);
    if (window->KeyDown(VK_UP))
        Translate(0, -delta);
    if (window->KeyDown(VK_DOWN))
        Translate(0, delta);

    // rotaciona avião
    if (window->KeyDown('Z'))
        Rotate(-0.5f * delta);
    if (window->KeyDown('X'))
        Rotate(0.5f * delta);

    // reinicia ao estado inicial 
    if (window->KeyDown('R'))
    {
        MoveTo(window->CenterX(), window->CenterY());
        RotateTo(0);
        direction.angle = 90.0f;
        direction.magnitude = 1.0f;
    }

    // dispara míssil
    if (window->KeyPress(VK_SPACE))
    {
        Vector2D::audio->Play(PULSE);
        Vector2D::scene->Add(new Missile(this, missile), STATIC);
    }

    // -----------------
    // Controle
    // -----------------

    if (gamepadOn)
    {
        // lê estado atualizado do controle
        gamepad->UpdateState();

        // movimenta com o analógico esquerdo
        Translate(gamepad->Axis(AxisX) * 0.25f * gameTime, gamepad->Axis(AxisY) * 0.25f * gameTime);

        // rotaciona com os gatilhos
        Rotate(-delta * gamepad->Axis(AxisZ) * 0.0005f);

        // reinicia posição do avião
        if (gamepad->ButtonPress(RESTART))
        {
            MoveTo(window->CenterX(), window->CenterY());
            RotateTo(0);
            direction.angle = 90.0f;
            direction.magnitude = 1.0f;
        }

        // movimento com o D-pad
        switch (gamepad->Dpad(DPAD))
        {
        case 0:
            Translate(0.0f, -delta);    // para cima
            break;
        case 4500:
            Translate(delta, -delta);   // para cima e direita
            break;
        case 9000:
            Translate(delta, 0.0f);     // para direita
            break;
        case 13500:
            Translate(delta, delta);    // para baixo e direita
            break;
        case 18000:
            Translate(0.0f, delta);     // para baixo
            break;
        case 22500:
            Translate(-delta, delta);   // para baixo e esquerda
            break;
        case 27000:
            Translate(-delta, 0.0f);   // para esquerda
            break;
        case 31500:
            Translate(-delta, -delta);  // para cima e esquerda
            break;
        }

        // dispara míssil
        if (gamepad->ButtonPress(SHOOT))
        {
            Vector2D::audio->Play(PULSE);
            Vector2D::scene->Add(new Missile(this, missile), STATIC);
        }
    }
}

// -------------------------------------------------------------------------------

void Plane::Draw()
{
    // desenha sprite do avião
    sprite->Draw(x, y, z, scale, rotation);

    // define cor do texto
    Color textColor{ 0.65f, 0.65f, 0.65f, 1.0f };

    // exibe informações sobre o avião
    text.str("");
    text << "Deslocamento Vetorial";
    font->Draw(45, 64, text.str(), textColor);

    text.str("");
    text << "Posição do avião: " << int(x) << " x " << int(y);
    font->Draw(45, 104, text.str(), textColor);

    text.str("");
    text << "Direção do Avião: " << int(direction.angle) << "°";
    font->Draw(45, 124, text.str(), textColor);

    text.str("");
    text << "Mísseis ativos: " << Vector2D::scene->Size() - 1;
    font->Draw(45, 144, text.str(), textColor);

    if (gamepadOn)
    {
        text.str("");
        text << "A        Disparo       L Stick     Translação           Rotação    LT  RT      Reiniciar     Start";
        font->Draw(window->CenterX() - 218.0f, window->Height() - 6.0f, text.str(), textColor);
    }
    else
    {
        text.str("");
        text << "Espaço    Disparo        Setas     Translação           Rotação      Z | X       Reiniciar        R";
        font->Draw(window->CenterX() - 233.0f, window->Height() - 6.0f, text.str(), textColor);
    }
}

// -------------------------------------------------------------------------------