/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     12 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   O carro do jogador
//
**********************************************************************************/

#include "Player.h"
#include "TopGear.h"

// ---------------------------------------------------------------------------------

Player::Player() : speed(TopGear::speed)
{
    // carrega fonte de exibição da velocidade
    speedFont = new Font("Resources/Digital80.png");
    speedFont->Spacing("Resources/Digital80.dat");

    // carrega folhas de sprites do carro
    carSet = new TileSet("Resources/RedCar.png", 164, 96, 6, 6);
    carAni = new Animation(carSet, 0.100f, true);

    uint straight[2] = { 0, 1 };
    uint left[2] = { 2,3 };
    uint right[2] = { 4,5 };

    carAni->Add(RIGHT, right, 2);
    carAni->Add(LEFT, left, 2);
    carAni->Add(STRAIGHT, straight, 2);

    // cria bounding box
    BBox(new Rect(-80.0f, -40.0f, 80.0f, 48.0f));

    // configura posição do objeto
    MoveTo(window->CenterX(), window->CenterY() + 200.0f);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete carAni;
    delete carSet;
    delete speedFont;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    // acelera ou freia
    if (window->KeyDown(VK_UP))
        speed += 500 * gameTime;
    if (window->KeyDown(VK_DOWN))
        speed -= 1000 * gameTime;

    // limita velocidade máxima e mínima
    if (speed > 3000) 
        speed = 3000;
    else 
        if (speed < 0) 
            speed = 0;

    // usa a velocidade para ajustar o som do motor
    TopGear::audio->Frequency(ENGINE, 0.5f + speed / 2000.0f);

    // deslocamento leva em conta a velocidade
    float deltaX = 600 * (pow(speed,0.5f) / 60.0f) * gameTime;

    // giro do volante do carro
    if (window->KeyDown(VK_LEFT))
    {
        Translate(-deltaX, 0);
        if (speed > 0)
            carAni->Select(LEFT);
    }
    if (window->KeyDown(VK_RIGHT))
    {
        Translate(deltaX, 0);
        if (speed > 0)
            carAni->Select(RIGHT);
    }
    if ((window->KeyUp(VK_LEFT) && window->KeyUp(VK_RIGHT)) || 
        (window->KeyDown(VK_LEFT) && window->KeyDown(VK_RIGHT)))
    {
        carAni->Select(STRAIGHT);
    }

    // se mantém sempre dentro da pista
    if (x < 180)
    {
        carAni->Select(STRAIGHT);
        MoveTo(180.0f, y);
    }
    else if (x > 780)
    {
        carAni->Select(STRAIGHT);
        MoveTo(780.0f, y);
    }
    
    // animação dos pneus deve se ajustar com a velocidade
    if (speed > 0)
    {
        carAni->Delay(50.0f/speed);
        carAni->NextFrame();
    }
}

// -------------------------------------------------------------------------------

void Player::Draw()
{
    // desenha carro
    carAni->Draw(x, y, Layer::FRONT);

    // desenha velocidade
    text.str("");
    text.width(3);
    text.fill('0');
    text << int(speed / 10.0f);
    speedFont->Draw(790, 222, "888", Color(0.1f, 0.1f, 0.1f, 1.0f));
    speedFont->Draw(790, 222, text.str(), Color(1.0f, 0.0f, 0.0f, 1.0f));
}

// -------------------------------------------------------------------------------