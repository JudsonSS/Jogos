/**********************************************************************************
// TrashCan (Código Fonte)
//
// Criação:     06 Ago 2019
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Lixeira
//
**********************************************************************************/

#include "FlyDemo.h"
#include "TrashCan.h"
#include "Fly.h"

// ---------------------------------------------------------------------------------

TrashCan::TrashCan()
{
    flyImg = new Image("Resources/Fly.png");
    cover = new Sprite("Resources/Cover.png");
    message = new Sprite("Resources/Message.png");
    warning = new Sprite("Resources/Warning.png");

    Point vet[12] = 
    { 
        Point(-19,-44), Point(30,-44), Point(32,-27), 
        Point(62,-12), Point(82,7), Point(77,30), 
        Point(29,44),Point(-30,44),Point(-82,25),
        Point(-82,2), Point(-53,-19), Point(-22,-28)
    };

    BBox(new Poly(vet, 12));
    MoveTo(526, 272);
    type = TRASHCAN;

    openCover = false;
    rFactor = 20;
}

// ---------------------------------------------------------------------------------

TrashCan::~TrashCan()
{
    delete flyImg;
    delete cover;
    delete message;
    delete warning;
}

// -------------------------------------------------------------------------------

void TrashCan::OnCollision(Object* obj)
{
    // rotaciona a tampa da lixeira
    Rotate(rFactor * gameTime);
    
    // se a lixeira está aberta
    if (openCover)
    {
        // balança tampa usando rotação
        if (rotation > 12)
            rFactor = -20;
        else if (rotation < 8)
            rFactor = 20;

        // se clicar na lixeira
        if (window->KeyPress(VK_LBUTTON))
        {
            RotateTo(0);
            Translate(-24, 2);
            openCover = false;

            // deleta moscas da cena
            FlyDemo::scene->Begin();
            Object* obj = nullptr;
            while ((obj = FlyDemo::scene->Next()) != nullptr)
            {
                if (obj->Type() == FLY)
                    FlyDemo::scene->Delete();
            }
        }
    }
    else
    {
        // balança tampa usando rotação
        if (rotation > 2)
            rFactor = -20;
        else if (rotation < -2)
            rFactor = 20;

        // se clicar na lixeira
        if (window->KeyPress(VK_LBUTTON))
        {
            Rotate(10);
            Translate(24, -2);
            openCover = true;

            // insere moscas na cena
            for (int i = 0; i < maxFlies; i++)
                FlyDemo::scene->Add(new Fly(flyImg), STATIC);
        }
    }
}

// -------------------------------------------------------------------------------

void TrashCan::Update()
{

}

// -------------------------------------------------------------------------------

void TrashCan::Draw()
{
    if (openCover)
    {
        // exibe mensagem de tampa aberta
        warning->Draw(175, 315);
        cover->Draw(x,y,z, scale, rotation);
    }
    else
    {
        // exibe mensagem de conscientização
        message->Draw(175, 315);
        cover->Draw(x, y, z, scale, rotation);
    }
}

// -------------------------------------------------------------------------------