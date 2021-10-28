/**********************************************************************************
// Rock (Código Fonte)
//
// Criação:     18 Mar 2013
// Atualização: 25 Jul 2019
// Compilador:  Visual C++ 2019
//
// Descrição:   Rocha espacial
//
**********************************************************************************/

#include "Rock.h"
#include "Debris.h"
#include "Explosion.h"
#include "Asteroids.h"


// ---------------------------------------------------------------------------------
// inicialização de membros estáticos

TileSet * Rock::tile = nullptr;
uint      Rock::count = 0;

// ---------------------------------------------------------------------------------

Rock::Rock()
{
    // usa uma única folha de sprites para todas as rochas
    if (!tile)
        tile = new TileSet("Resources/Asteroids.png", 128, 128, 4, 4);

    // usa animação para desenhar rochas da folha
    anim = new Animation(tile, 0.020f, false);

    // define bounding box das rochas
    Point rocksVertex[4][8] =
    {
        { Point(-11, -45), Point(12, -47), Point(38, -27), Point(46, 12), Point(37, 28), Point(-4, 53), Point(-33, 37), Point(-43, -20) },
        { Point(-10, -46), Point(41, -34), Point(52, 2), Point(44, 28), Point(18, 47), Point(-24, 47), Point(-44, 32), Point(-39, -12) },
        { Point(-4, -44), Point(40, -21), Point(43, 20), Point(37, 29), Point(-1, 49), Point(-34, 36), Point(-46, -11), Point(-19, -39) },
        { Point(-6, -46), Point(13, -42), Point(35, -16), Point(47, 25), Point(30, 42), Point(2, 50), Point(-46, 13), Point(-44, -8) }
    };
    
    // seleciona aleatoriamente uma rocha do tileset
    frame = RandFrame(mt);

    // cria bounding box
    BBox(new Poly(rocksVertex[frame], 8));
    
    // move para posição aleatória dentro da tela
    MoveTo(RandWidth(mt), RandHeight(mt));
    
    // usa uma escala aleatória entre 0.8 e 1.0
    ScaleTo(1.0f - 0.02f * RandFactor(mt));

    // define aleatoriamente giro e velocidade  
    spin = -25.0f + (5.0f * RandFactor(mt));        // -25.0 a +25.0
    speed.RotateTo(RandAngle(mt));                  // 0 a 359
    speed.ScaleTo(5.0f + RandFactor(mt));           // 5.0 a 15.0

    // mais uma rocha criada
    count++;

    // tipo do objeto
    type = ROCK;
}

// ---------------------------------------------------------------------------------

Rock::~Rock()
{
    // remove tileset se for a última rocha
    if (--count == 0)
        delete tile;

    delete anim;
}

// ---------------------------------------------------------------------------------

void Rock::OnCollision(Object * obj)
{
    if (obj->Type() == ROCK)
    {
        // ------------------------
        // Colisão entre asteroides
        // ------------------------

        Rock* rockA = this;
        Rock* rockB = static_cast<Rock*>(obj);

        // centros das rochas
        Point pA { rockA->X(), rockA->Y() };
        Point pB { rockB->X(), rockB->Y() };

        // ângulo formado pela linha que interliga os centros das rochas
        float angleA = Line::Angle(pA, pB);
        float angleB = angleA + 180.0f;

        // mantém ângulo na faixa de 0 a 359 graus
        if (angleB > 360)
            angleB -= 360.0f;

        // vetores gerados no impacto (com 25% de perda)
        Vector impactA{ angleA, 0.75f * rockA->speed.Magnitude() };
        Vector impactB{ angleB, 0.75f * rockB->speed.Magnitude() };

        // adiciona vetor impacto à velocidade das rochas
        rockA->speed.Add(impactB);
        rockB->speed.Add(impactA);

        // limita velocidade das rochas
        if (rockB->speed.Magnitude() > 15.0f)
            rockB->speed.ScaleTo(15.0f);

        if (rockA->speed.Magnitude() > 15.0f)
            rockA->speed.ScaleTo(15.0f);
    }
    else
    {
        // ---------------------------------------
        // Colisão de asteroide com míssil ou nave
        // ---------------------------------------

        // toca som de explosão
        Asteroids::audio->Play(EXPLOSION);
        
        // remove asteroide
        Asteroids::scene->Delete(this, MOVING);

        // remove míssil da cena
        if (obj->Type() == MISSILE)
        {
            Explosion* explo = new Explosion(obj->X(), obj->Y());
            Asteroids::scene->Add(explo, STATIC);
            Asteroids::scene->Delete(obj, MOVING);
        }
        
        // se colisão ocorreu com um asteroide grande ou médio
        if (scale > 0.5f)
        {
            // cria fragmentos de rocha na posição de contato
            Asteroids::scene->Add(new Debris(obj->X(), obj->Y()), STATIC);

            // cria dois asteroids
            Rock * rockA = new Rock();
            Rock * rockB = new Rock();
            rockA->MoveTo(x, y);
            rockB->MoveTo(x, y);
            
            // asteroide grande gera dois médios
            if (scale > 0.75f)
            {
                rockB->Scale(0.70f);
                rockA->Scale(0.70f);
            }
            // asteroide médio gera dois pequenos
            else
            {
                rockB->Scale(0.40f);
                rockA->Scale(0.40f);
            }

            // adiciona dois asteroides menores na cena
            Asteroids::scene->Add(rockA, MOVING);
            Asteroids::scene->Add(rockB, MOVING);
        }
        // se colisão ocorreu com um asteroide pequeno
        else
        {
            // cria fragmentos de rocha no centro do asteroid
            Asteroids::scene->Add(new Debris(x, y), STATIC);

            // se a quantidade de asteroides está baixa
            if (count <= 50)
            {
                // adiciona asteroide grande na cena
                Rock * rock = new Rock();

                // pega tamanho do asteroid pela sua bounding box
                Poly * pol = static_cast<Poly*>(rock->BBox());

                // usa o raio como metade do tamanho do asteroide
                float half = pol->BBox()->Radius();

                // asteroide nasce fora da tela
                rock->MoveTo(RandWidth(mt), -half);

                // adiciona asteroid na cena
                Asteroids::scene->Add(rock, MOVING);
            }
        }
    }    
}

// ---------------------------------------------------------------------------------

void Rock::Update()
{
    // rotaciona rocha pelo fator de rotação
    Rotate(spin * gameTime);

    // move rocha usando o vetor velocidade
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

    // pega tamanho do asteroid pela sua bounding box
    Poly * pol = static_cast<Poly*>(BBox());

    // usa o raio como metade do tamanho do asteroide
    float half = pol->BBox()->Radius();

    // passa rochas de um lado para outro da janela
    if (x + half < 0)
        MoveTo(float(window->Width()) + half, y);
    if (x - half > window->Width())
        MoveTo(-half, y);
    if (y + half < 0)
        MoveTo(x, float(window->Height()) + half);
    if (y - half > window->Height())
        MoveTo(x, -half);
}

// ---------------------------------------------------------------------------------