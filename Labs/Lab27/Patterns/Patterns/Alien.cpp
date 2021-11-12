/**********************************************************************************
// Alien (Código Fonte)
// 
// Criação:     25 Mar 2013
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Executa scripts com padrões de movimentação
//
**********************************************************************************/

#include "Alien.h"
#include "Stage.h"
#include "Patterns.h"
#include "Explosion.h"
#include <cmath>

// ---------------------------------------------------------------------------------

Alien::Alien(uint alien, Instruction * vet, int tam, float pX, float pY) 
    : angle(-8,8), magnitude(1,8)
{
    // tipo do alien
    type = alien;

    // faz cópia do script 
    script = new Instruction[tam];
    for (int i=0; i < tam; i++)
        script[i] = vet[i];

    // carrega tileset do objeto
    switch (type)
    {
    case ALIEN1: alienSet = new TileSet("Resources/Alien1.png", 26, 20, 2, 2); break;
    case ALIEN2: alienSet = new TileSet("Resources/Alien2.png", 26, 20, 2, 2); break;
    case ALIEN3: alienSet = new TileSet("Resources/Alien3.png", 28, 28, 2, 2); break;
    case ALIEN4: alienSet = new TileSet("Resources/Alien4.png", 28, 28, 2, 2); break;
    }
    anim = new Animation(alienSet, 0.500, true);
    
    // configuração inicial do objeto
    BBox(new Rect(-13, -10, 13, 10));
    MoveTo(pX, pY);
    speed = { 0.0f, 0.0f };

    // inicia execução do script
    index = 0;
    end = tam - 1;
    duration = script[index].duration;
    timer.Start();

    // mais um inimigo
    ++Stage::enemies;
}

// ---------------------------------------------------------------------------------

Alien::~Alien()
{
    delete [] script;
    delete alienSet;
    delete anim;

    // menos um inimigo
    --Stage::enemies;
}

// ---------------------------------------------------------------------------------

void Alien::OnCollision(Object * obj)
{
    // se colidiu com um míssil
    if (obj->Type() == MISSILE)
    {
        // deleta missíl
        Patterns::scene->Delete(obj, STATIC);

        // toca som de acordo com o alien atingido
        switch (type)
        {
        case ALIEN1: Patterns::audio->Play(ALIEN1); break;
        case ALIEN2: Patterns::audio->Play(ALIEN2); break;
        case ALIEN3: Patterns::audio->Play(ALIEN3); break;
        case ALIEN4: Patterns::audio->Play(ALIEN4); break;
        }

        if (type == ALIEN3)
        {
            // o alien 3 vira o alien 4 ao ser atingido
            delete anim;
            delete alienSet;
            alienSet = new TileSet("Resources/Alien4.png", 28, 28, 2, 2);
            anim = new Animation(alienSet, 0.500, true);
            type = ALIEN4;
        }
        else
        {
            // qualquer outro alien morre com um tiro
            Patterns::scene->Add(new Explosion(x, y), STATIC);
            Patterns::scene->Delete(this, MOVING);            
        }
    }
}

// -------------------------------------------------------------------------------

void Alien::Update()
{
    // deslocamento padrão
    float delta = 50 * gameTime;

    // atualiza animações
    anim->NextFrame();

    // ----------------------------
    // Próxima instrução do script
    // ----------------------------

    if (script[index].instruction == MOVETO || script[index].instruction == SLIDETO)
    {
        // pega posição X e Y de destino
        float targetX = script[index].angle;
        float targetY = script[index].magnitude;

        // se chegou bem próximo do destino
        if (abs(x - targetX) < 2 && abs(y - targetY) < 2)
        {
            // move exatamente para a posição de destino
            MoveTo(targetX, targetY);

            // passa para a próxima instrução
            index = (index == end ? index : ++index);
            duration = script[index].duration;
            timer.Start();
        }
    }
    else
    {
        // se esgotou o tempo da instrução
        if (timer.Elapsed(duration))
        {
            // passa para a próxima instrução
            index = (index == end ? index : ++index);
            duration = script[index].duration;
            timer.Start();
        }
    }

    // ------------------------
    // Interpretador do script
    // ------------------------
  
    // realiza salto antes de qualquer outra instrução
    if (script[index].instruction == JUMP)
    {
        index = int(script[index].angle);
        duration = script[index].duration;
        timer.Start();
    }

    switch (script[index].instruction)
    {
    case MOVE:    // MOVE | Ângulo | Magnitude | Duração
        speed.RotateTo(script[index].angle);
        speed.ScaleTo(script[index].magnitude);
        RotateTo(-speed.Angle() + 90);
        break;

    case MOVETO:  // MOVETO | PosX | PosY | Magnitude
        speed.RotateTo(Line::Angle(Point(x, y), Point(script[index].angle, script[index].magnitude)));
        speed.ScaleTo(script[index].duration);
        RotateTo(-speed.Angle() + 90);
        break;

    case SLIDE:   // SLIDE | Ângulo | Magnitude | Duração
        speed.RotateTo(script[index].angle);
        speed.ScaleTo(script[index].magnitude);
        break;

    case SLIDETO: // SLIDETO | PosX | PosY | Magnitude
        speed.RotateTo(Line::Angle(Point(x, y), Point(script[index].angle, script[index].magnitude)));
        speed.ScaleTo(script[index].duration);
        break;

    case TURN:    // TURN | Ângulo | Magnitude | Duração
    {
        Vector target{ script[index].angle, script[index].magnitude * delta };
        speed.Add(target);
        RotateTo(-speed.Angle() + 90);
        break;
    }
    case ROTATE:  // ROTATE | Ângulo | Magnitude | Duração
        speed.Rotate(-script[index].angle * delta);
        speed.ScaleTo(script[index].magnitude);
        Rotate(-script[index].angle * delta);
        break;

    case RANDOM:  // RANDOM | Ângulo | Magnitude | Duração
        speed.Rotate(-angle.Rand());
        speed.ScaleTo(magnitude.Rand());
        RotateTo(-speed.Angle() + 90);
        break;
    }

    // desloca objeto pelo seu vetor velocidade
    Translate(speed.XComponent() * delta, -speed.YComponent() * delta);
}

// -------------------------------------------------------------------------------