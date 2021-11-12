/**********************************************************************************
// Stage (Código Fonte)
//
// Criação:     09 Ago 2019
// Atualização: 10 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Cria um estágio do jogo
//
**********************************************************************************/

#include "Stage.h"
#include "Patterns.h"

// ------------------------------------------------------------------------------

uint Stage::enemies = 0;

// ------------------------------------------------------------------------------

Stage::Stage()
{
    // carrega sprite
    logo = new Sprite("Resources/Galaga.png");

    // -------------
    // primeira onda
    // -------------

    const int size1 = 9;
    Instruction entrance1[size1] =
    {
        { MOVETO, 340.0f, 0.0f, 5.0f },
        { MOVETO, 50.0f, 320.0f, 5.0f },
        { ROTATE, 5.0f, 8.0f, 0.8f },
        { MOVE, 90.0f, 5.0f, 0.5f },
        { MOVETO, 300.0f, 100.0f, 5.0f },
        { MOVE, 270.0f, 0.0f, 1.0f },
        { SLIDE, 180.0f, 0.5f, 5.0f },
        { SLIDE, 0.0f, 0.5f, 5.0f },
        { JUMP, 6.0f, 0.0f, 0.0f }
    };

    entrance1[4].angle = 300.0f;
    first[0] = new Alien(ALIEN1, entrance1, size1, 340.0f, 0);
    entrance1[4].angle = 340.0f;
    first[1] = new Alien(ALIEN1, entrance1, size1, 340.0f, -50);
    entrance1[4].angle = 380.0f;
    first[2] = new Alien(ALIEN1, entrance1, size1, 340.0f, -100);
    entrance1[4].angle = 420.0f;
    first[3] = new Alien(ALIEN1, entrance1, size1, 340.0f, -150);

    // -------------
    // segunda onda
    // -------------

    const int size2 = 9;
    Instruction entrance2[size2] =
    {
        { MOVETO, 380.0f, 0.0f, 5.0f },
        { MOVETO, 669.0f, 320.0f, 5.0f },
        { ROTATE, -5.0f, 8.0f, 0.8f },
        { MOVE, 90.0f, 5.0f, 0.5f },
        { MOVETO, 420.0f, 150.0f, 5.0f },
        { MOVE, 270.0f, 0.0f, 1.0f },
        { SLIDE, 0.0f, 0.5f, 5.0f },
        { SLIDE, 180.0f, 0.5f, 5.0f },
        { JUMP, 6.0f, 0.0f, 0.0f }
    };

    entrance2[4].angle = 420.0f;
    second[0] = new Alien(ALIEN2, entrance2, size2, 380.0f, 0);
    entrance2[4].angle = 380.0f;
    second[1] = new Alien(ALIEN2, entrance2, size2, 380.0f, -50);
    entrance2[4].angle = 340.0f;
    second[2] = new Alien(ALIEN2, entrance2, size2, 380.0f, -100);
    entrance2[4].angle = 300.0f;
    second[3] = new Alien(ALIEN2, entrance2, size2, 380.0f, -150);

    // -------------
    // terceira onda
    // -------------

    const int size3 = 5;
    Instruction entrance3[size3] =
    {
        { MOVETO, 120.0f, 400.0f, 5.0f },
        { ROTATE, 5.0f, 8.0f, 1.8f },
        { MOVE, 90.0f, 5.0f, 0.3f },
        { MOVETO, 300.0f, 50.0f, 5.0f },
        { MOVE, 270.0f, 0.0f, 5.0f }
    };

    entrance3[3].angle = 300.0f;
    entrance3[3].magnitude = 50.0f;
    third[0] = new Alien(ALIEN3, entrance3, size3, 0, 400);
    entrance3[3].angle = 300.0f;
    entrance3[3].magnitude = 200.0f;
    third[1] = new Alien(ALIEN1, entrance3, size3, -45, 400);
    entrance3[3].angle = 340.0f;
    entrance3[3].magnitude = 50.0f;
    third[2] = new Alien(ALIEN3, entrance3, size3, -90, 400);
    entrance3[3].angle = 340.0f;
    entrance3[3].magnitude = 200.0f;
    third[3] = new Alien(ALIEN1, entrance3, size3, -135, 400);
    entrance3[3].angle = 380.0f;
    entrance3[3].magnitude = 50.0f;
    third[4] = new Alien(ALIEN3, entrance3, size3, -180, 400);
    entrance3[3].angle = 380.0f;
    entrance3[3].magnitude = 200.0f;
    third[5] = new Alien(ALIEN1, entrance3, size3, -225, 400);
    entrance3[3].angle = 420.0f;
    entrance3[3].magnitude = 50.0f;
    third[6] = new Alien(ALIEN3, entrance3, size3, -270, 400);
    entrance3[3].angle = 420.0f;
    entrance3[3].magnitude = 200.0f;
    third[7] = new Alien(ALIEN1, entrance3, size3, -315, 400);

    // -------------
    // quarta onda
    // -------------

    const int size4 = 5;
    Instruction entrance4[size4] =
    {
        { MOVETO, 600.0f, 500.0f, 5.0f },
        { ROTATE, -5.0f, 8.0f, 1.8f },
        { MOVE, 90.0f, 5.0f, 0.3f },
        { MOVETO, 220.0f, 50.0f, 5.0f },
        { MOVE, 270.0f, 0.0f, 5.0f }
    };

    entrance4[3].angle = 220.0f;
    entrance4[3].magnitude = 50.0f;
    forth[0] = new Alien(ALIEN1, entrance4, size4, window->Width() + 0, 500);
    entrance4[3].angle = 220.0f;
    entrance4[3].magnitude = 200.0f;
    forth[1] = new Alien(ALIEN1, entrance4, size4, window->Width() + 45, 500);
    entrance4[3].angle = 260.0f;
    entrance4[3].magnitude = 50.0f;
    forth[2] = new Alien(ALIEN1, entrance4, size4, window->Width() + 90, 500);
    entrance4[3].angle = 260.0f;
    entrance4[3].magnitude = 200.0f;
    forth[3] = new Alien(ALIEN1, entrance4, size4, window->Width() + 135, 500);
    entrance4[3].angle = 460.0f;
    entrance4[3].magnitude = 50.0f;
    forth[4] = new Alien(ALIEN1, entrance4, size4, window->Width() + 180, 500);
    entrance4[3].angle = 460.0f;
    entrance4[3].magnitude = 200.0f;
    forth[5] = new Alien(ALIEN1, entrance4, size4, window->Width() + 225, 500);
    entrance4[3].angle = 500.0f;
    entrance4[3].magnitude = 50.0f;
    forth[6] = new Alien(ALIEN1, entrance4, size4, window->Width() + 270, 500);
    entrance4[3].angle = 500.0f;
    entrance4[3].magnitude = 200.0f;
    forth[7] = new Alien(ALIEN1, entrance4, size4, window->Width() + 315, 500);

    // -------------
    // quinta onda
    // -------------

    const int size5 = 10;
    Instruction entrance5[size5] =
    {
        { MOVETO, 100.0f, 300.0f, 5.0f },
        { ROTATE, 5.0f, 8.0f, 0.4f },
        { MOVE, 0.0f, 5.0f, 1.2f },
        { ROTATE, 5.0f, 4.0f, 0.7f },
        { MOVE, 180.0f, 5.0f, 0.1f },
        { MOVETO, 220.0f, 250.0f, 5.0f },
        { MOVE, 270.0f, 0.0f, 3.0f },
        { SLIDE, 180.0f, 0.5f, 5.0f },
        { SLIDE, 0.0f, 0.5f, 5.0f },
        { JUMP, 7.0f, 0.0f, 0.0f }
    };

    entrance5[5].angle = 220.0f;
    entrance5[5].magnitude = 250.0f;
    fifth[0] = new Alien(ALIEN2, entrance5, size5, 100, 0);
    entrance5[5].angle = 260.0f;
    entrance5[5].magnitude = 250.0f;
    fifth[1] = new Alien(ALIEN2, entrance5, size5, 100, -50);
    entrance5[5].angle = 220.0f;
    entrance5[5].magnitude = 300.0f;
    fifth[2] = new Alien(ALIEN2, entrance5, size5, 100, -100);
    entrance5[5].angle = 260.0f;
    entrance5[5].magnitude = 300.0f;
    fifth[3] = new Alien(ALIEN2, entrance5, size5, 100, -150);

    // inverte SLIDE para os próximos
    entrance5[7].angle = 0.0f;
    entrance5[8].angle = 180.0f;
    // --
    entrance5[5].angle = 460.0f;
    entrance5[5].magnitude = 250.0f;
    fifth[4] = new Alien(ALIEN2, entrance5, size5, 100, -200);
    entrance5[5].angle = 500.0f;
    entrance5[5].magnitude = 250.0f;
    fifth[5] = new Alien(ALIEN2, entrance5, size5, 100, -250);
    entrance5[5].angle = 460.0f;
    entrance5[5].magnitude = 300.0f;
    fifth[6] = new Alien(ALIEN2, entrance5, size5, 100, -300);
    entrance5[5].angle = 500.0f;
    entrance5[5].magnitude = 300.0f;
    fifth[7] = new Alien(ALIEN2, entrance5, size5, 100, -350);

    // -------------

    const int size6 = 9;
    Instruction entrance6[size6] =
    {
        { MOVETO, 619.0f, 250.0f, 5.0f },
        { ROTATE, -5.0f, 8.0f, 0.4f },
        { MOVE, 180.0f, 5.0f, 1.2f },
        { ROTATE, 5.0f, 4.0f, 0.7f },
        { MOVE, 0.0f, 5.0f, 1.2f },
        { ROTATE, 5.0f, 4.0f, 0.7f },
        { MOVE, 180.0f, 5.0f, 0.3f },
        { MOVETO, 220.0f, 300.0f, 5.0f },
        { MOVE, 270.0f, 0.0f, 10.0f }
    };

    entrance6[7].angle = 300.0f;
    entrance6[7].magnitude = 250.0f;
    sixth[0] = new Alien(ALIEN2, entrance6, size6, 619, 0);
    entrance6[7].angle = 300.0f;
    entrance6[7].magnitude = 300.0f;
    sixth[1] = new Alien(ALIEN2, entrance6, size6, 619, -50);
    entrance6[7].angle = 340.0f;
    entrance6[7].magnitude = 250.0f;
    sixth[2] = new Alien(ALIEN2, entrance6, size6, 619, -100);
    entrance6[7].angle = 340.0f;
    entrance6[7].magnitude = 300.0f;
    sixth[3] = new Alien(ALIEN2, entrance6, size6, 619, -150);
    entrance6[7].angle = 380.0f;
    entrance6[7].magnitude = 250.0f;
    sixth[4] = new Alien(ALIEN2, entrance6, size6, 619, -200);
    entrance6[7].angle = 380.0f;
    entrance6[7].magnitude = 300.0f;
    sixth[5] = new Alien(ALIEN2, entrance6, size6, 619, -250);
    entrance6[7].angle = 420.0f;
    entrance6[7].magnitude = 250.0f;
    sixth[6] = new Alien(ALIEN2, entrance6, size6, 619, -300);
    entrance6[7].angle = 420.0f;
    entrance6[7].magnitude = 300.0f;
    sixth[7] = new Alien(ALIEN2, entrance6, size6, 619, -350);

    // -------------

    timer.Start();
    fase1 = false;
    fase2 = false;
    fase3 = false;
    fase4 = false;

    // inicia música
    Patterns::audio->Play(MUSIC);
}

// ------------------------------------------------------------------------------

Stage::~Stage()
{
    delete logo;

    // libera aliens que não foram inseridos na cena
    if (!fase1)
    {
        for (auto elem : first)
            delete elem;

        for (auto elem : second)
            delete elem;
    }

    if (!fase2)
    {
        for (auto elem : third)
            delete elem;
    }

    if (!fase3)
    {
        for (auto elem : forth)
            delete elem;
    }

    if (!fase4)
    {
        for (auto elem : fifth)
            delete elem;

        for (auto elem : sixth)
            delete elem;
    }
}

// -------------------------------------------------------------------------------

void Stage::Update()
{
    if (!fase1 && timer.Elapsed(7.0f))
    {
        Patterns::scene->Add(first[0], MOVING);
        Patterns::scene->Add(first[1], MOVING);
        Patterns::scene->Add(first[2], MOVING);
        Patterns::scene->Add(first[3], MOVING);

        Patterns::scene->Add(second[0], MOVING);
        Patterns::scene->Add(second[1], MOVING);
        Patterns::scene->Add(second[2], MOVING);
        Patterns::scene->Add(second[3], MOVING);

        fase1 = true;
    }

    if (!fase2 && timer.Elapsed(12.0f))
    {
        Patterns::scene->Add(third[0], MOVING);
        Patterns::scene->Add(third[1], MOVING);
        Patterns::scene->Add(third[2], MOVING);
        Patterns::scene->Add(third[3], MOVING);
        Patterns::scene->Add(third[4], MOVING);
        Patterns::scene->Add(third[5], MOVING);
        Patterns::scene->Add(third[6], MOVING);
        Patterns::scene->Add(third[7], MOVING);

        fase2 = true;
    }

    if (!fase3 && timer.Elapsed(17.0f))
    {
        Patterns::scene->Add(forth[0], MOVING);
        Patterns::scene->Add(forth[1], MOVING);
        Patterns::scene->Add(forth[2], MOVING);
        Patterns::scene->Add(forth[3], MOVING);
        Patterns::scene->Add(forth[4], MOVING);
        Patterns::scene->Add(forth[5], MOVING);
        Patterns::scene->Add(forth[6], MOVING);
        Patterns::scene->Add(forth[7], MOVING);

        fase3 = true;
    }

    if (!fase4 && timer.Elapsed(20.0f))
    {
        Patterns::scene->Add(fifth[0], MOVING);
        Patterns::scene->Add(fifth[1], MOVING);
        Patterns::scene->Add(fifth[2], MOVING);
        Patterns::scene->Add(fifth[3], MOVING);
        Patterns::scene->Add(fifth[4], MOVING);
        Patterns::scene->Add(fifth[5], MOVING);
        Patterns::scene->Add(fifth[6], MOVING);
        Patterns::scene->Add(fifth[7], MOVING);

        Patterns::scene->Add(sixth[0], MOVING);
        Patterns::scene->Add(sixth[1], MOVING);
        Patterns::scene->Add(sixth[2], MOVING);
        Patterns::scene->Add(sixth[3], MOVING);
        Patterns::scene->Add(sixth[4], MOVING);
        Patterns::scene->Add(sixth[5], MOVING);
        Patterns::scene->Add(sixth[6], MOVING);
        Patterns::scene->Add(sixth[7], MOVING);

        fase4 = true;
    }

    if (enemies == 0 && fase1 && fase2 && fase3 && fase4)
    {
        Patterns::scene->Delete();
        Patterns::scene->Add(new Stage(), STATIC);
    }
}

// -------------------------------------------------------------------------------

void Stage::Draw()
{
    if (!timer.Elapsed(7.0f))
        logo->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
}

// -------------------------------------------------------------------------------
