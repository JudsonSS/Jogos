/**********************************************************************************
// Ship (Código Fonte)
// 
// Criação:     01 Out 2012
// Atualização: 18 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma nave espacial
//
**********************************************************************************/

#include "Ship.h"
#include "Missile.h"
#include "Inertia.h"

// ---------------------------------------------------------------------------------

Ship::Ship()
{
    // inicializa animação 
    shipSet = new TileSet("Resources/SpaceShip.png", 43, 60, 6, 6);
    shipAni = new Animation(shipSet, 0.060f, false); 

    uint seqInertia[] = {0};
    uint seqForwThrust[] = {1,2,3,4};
    uint seqBackThrust[] = {5};

    shipAni->Add(FORWARD, seqForwThrust, 4);
    shipAni->Add(BACKWARD, seqBackThrust, 1);
    shipAni->Add(INERTIA, seqInertia, 1);

    // posição inicial da nave
    MoveTo(window->CenterX(), window->CenterY());

    // escala e rotação da nave
    ScaleTo(0.8f); 
    RotateTo(0);
    
    // inicializa direção e velocidade da nave
    direction.RotateTo(90.0f);
    direction.ScaleTo(10.0f);
    speed.RotateTo(90.0f);
    speed.ScaleTo(0.0f);
}

// ---------------------------------------------------------------------------------

Ship::~Ship()
{
    delete shipSet;
    delete shipAni;
}

// ---------------------------------------------------------------------------------

void Ship::Forward()
{
    // impulsiona nave para frente
    direction.ScaleTo(20.0f * gameTime);
    speed.Add(direction);
}

// ---------------------------------------------------------------------------------

void Ship::Backward()
{
    // impulsiona nave para trás
    Vector thrust;
    thrust.RotateTo(direction.Angle() < 180 ?  direction.Angle() + 180.0f : direction.Angle() - 180.0f);
    thrust.ScaleTo(10.0f * gameTime);
    speed.Add(thrust);    
} 

// ---------------------------------------------------------------------------------

void Ship::Rotate(float angle)
{
    // rotaciona objeto e vetor
    Object::Rotate(angle);
    direction.Rotate(angle);
}

// -------------------------------------------------------------------------------

void Ship::Update()
{
    // deslocamento padrão
    float delta = 100 * gameTime;

    // rotaciona nave
    if (window->KeyDown(VK_RIGHT))
        Rotate(delta);
    if (window->KeyDown(VK_LEFT))
        Rotate(-delta);
    
    // impulsiona nave
    if (window->KeyDown(VK_UP))
        Forward();
    if (window->KeyDown(VK_DOWN))
        Backward();

    // sons e animação (usam KeyPress)
    if (window->KeyPress(VK_UP))
    {
        Inertia::audio->Play(JETUP);
        Inertia::audio->Play(LOOPUP, true);
        shipAni->Select(FORWARD);
    }
    if (window->KeyPress(VK_DOWN))
    {
        Inertia::audio->Play(JETDOWN);
        Inertia::audio->Play(LOOPDOWN, true);
        shipAni->Select(BACKWARD);
    }

    // liberação de teclas
    if (window->KeyUp(VK_UP) && window->KeyUp(VK_DOWN))
        shipAni->Select(INERTIA);

    if (window->KeyUp(VK_UP))
    {
        Inertia::audio->Stop(JETUP);
        Inertia::audio->Stop(LOOPUP);
    }
    if (window->KeyUp(VK_DOWN))
    {
        Inertia::audio->Stop(JETDOWN);
        Inertia::audio->Stop(LOOPDOWN);
    }

    // dispara míssil
    if (window->KeyPress(VK_SPACE))
    {
        Inertia::audio->Play(FIRE);
        Inertia::scene->Add(new Missile(this), MOVING);
    }

    // inércia desloca constantemente a nave através do vetor speed
    Translate(speed.XComponent() * 0.1f * delta, -speed.YComponent() * 0.1f * delta);    

    // faz a nave girar ao redor da tela
    if (x < 0)
        Translate(float(window->Width()), 0.0f);
    if (x > window->Width())
        Translate(float(-window->Width()), 0.0f);
    if (y < 0)
        Translate(0.0f, float(window->Height()));
    if (y > window->Height())
        Translate(0.0f, float(-window->Height()));
    
    // atualiza animação
    if (!shipAni->Inactive())
        shipAni->NextFrame();
}

// -------------------------------------------------------------------------------

void Ship::Draw()
{
    // desenha nave espacial 
    shipAni->Draw(x, y, z, scale, rotation);
}

// -------------------------------------------------------------------------------