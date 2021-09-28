/**********************************************************************************
// Scene (Código Fonte)
// 
// Criação:     16 Mar 2012
// Atualização: 20 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para gerenciar o cenário do jogo.
//
//              Um gerenciador de cena é responsável por guardar os objetos
//              da cena, atualizando-os e desenhando-os de forma mais prática.
//              Ele pode ser usado também para outras tarefas que impliquem em
//              percorrer a lista de objetos, como detecção de colisão.
//
**********************************************************************************/

#include "Scene.h"
#include "Object.h"
#include "Engine.h"

// ---------------------------------------------------------------------------------

Scene::Scene()
{

}

// ---------------------------------------------------------------------------------

Scene::~Scene()
{
    // remove da memória os objetos estáticos
    for (auto obj : statics)
        delete obj;

    // remove da memória os objetos em movimento
    for (auto obj : moving)
        delete obj;
}

// ---------------------------------------------------------------------------------


void Scene::Add(Object* obj, int type)
{
    // insere novo objeto na cena
    if (type == STATIC)
        statics.push_back(obj);
    else
        moving.push_back(obj);
}

// ---------------------------------------------------------------------------------

void Scene::Remove(Object* obj, int type)
{
    // remove objeto da cena
    if (type == STATIC)
        statics.remove(obj);
    else
        moving.remove(obj);
}

// ---------------------------------------------------------------------------------

void Scene::Remove()
{
    // remove objeto da cena
    if (processing == STATIC)
        statics.remove(*it);
    else
        moving.remove(*it);
}

// ---------------------------------------------------------------------------------

void Scene::Delete(Object* obj, int type)
{
    toDelete.push_back(ObjectDel{ obj, type });
}

// ---------------------------------------------------------------------------------

void Scene::Delete()
{
    toDelete.push_back(ObjectDel{ *it, processing });
}

// ---------------------------------------------------------------------------------

uint Scene::Size()
{
    return uint(moving.size() + statics.size());
}

// ---------------------------------------------------------------------------------

void Scene::ProcessDeleted()
{
    // remove objetos duplicados
    toDelete.sort();
    toDelete.unique();

    for (const auto & [obj, type] : toDelete)
    {
        // libera memória ocupada pelo objeto
        delete obj;

        // remove objeto da cena
        if (type == STATIC)
            statics.remove(obj);
        else
            moving.remove(obj);
    }

    // esvazia a lista 
    toDelete.clear();
}

// ---------------------------------------------------------------------------------

void Scene::Update()
{
    // atualiza todos os objetos estáticos
    processing = STATIC;
    for (it = statics.begin(); it != statics.end(); ++it)
        (*it)->Update();

    // atualiza todos os objetos em movimento
    processing = MOVING;
    for (it = moving.begin(); it != moving.end(); ++it)
        (*it)->Update();

    ProcessDeleted();
}

// ---------------------------------------------------------------------------------

void Scene::Draw()
{
    // desenha todos os objetos estáticos
    processing = STATIC;
    for (it = statics.begin(); it != statics.end(); ++it)
        (*it)->Draw();

    // desenha todos os objetos em movimento
    processing = MOVING;
    for (it = moving.begin(); it != moving.end(); ++it)
        (*it)->Draw();
}

// ---------------------------------------------------------------------------------

void Scene::DrawBBox()
{
    // inicia desenho de pixels
    Engine::renderer->BeginPixels();

    // desenha bounding box dos objetos estáticos
    for (const auto& obj : statics)
    {
        if (obj->BBox())
            Engine::renderer->Draw(obj->BBox(), 0xffff00ff);
    }

    // desenha bounding box dos objetos em movimento
    for (const auto& obj : moving)
    {
        if (obj->BBox())
            Engine::renderer->Draw(obj->BBox(), 0xffff00ff);
    }

    // finaliza desenho de pixels
    Engine::renderer->EndPixels();
}

// ---------------------------------------------------------------------------------

void Scene::Begin()
{
    // aponta para o primeiro elemento de cada lista
    its = statics.begin();
    itm = moving.begin();
    processing = STATIC;
}

// ---------------------------------------------------------------------------------

Object * Scene::Next()
{
    // se apontador aponta para objeto válido
    if (its != statics.end())
    {
        // passa ao próximo objeto
        // guarda apontador para o anterior
        it = its++;
        return *it;
    }
    else
        if (itm != moving.end())
        {
            processing = MOVING;
            it = itm++;
            return *it;
        }
        else
            // chegou ao fim das listas
            return nullptr;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Point* p, Point* q)
{
    // se as coordenadas inteiras são iguais 
    if (int(p->X()) == int(q->X()) && int(p->Y()) == int(q->Y()))
        return true;

    // caso contrário não há colisão
    return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Point * p, Rect * r)
{
    // se as coordenadas  do ponto estão dentro do retângulo
    if (p->X() >= r->Left() && p->X() <= r->Right())
        if (p->Y() >= r->Top() && p->Y() <= r->Bottom())
            return true;

    // caso contrário não há colisão
    return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Point * p, Circle * c)
{
    // se a distância entre o ponto e o centro do círculo
    // for menor que o raio do círculo então há colisão
    if (p->Distance(Point(c->CenterX(), c->CenterY())) <= c->radius)
        return true;
    else
        return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Rect * ra, Rect * rb)
{
    // verificando sobreposição no eixo x
    bool overlapX = (rb->Left() <= ra->Right() && ra->Left() <= rb->Right());

    // verificando sobreposição no eixo y
    bool overlapY = (rb->Top() <= ra->Bottom() && ra->Top() <= rb->Bottom());

    // existe colisão se há sobreposição nos dois eixos
    return overlapX && overlapY;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Rect * r, Circle * c)
{
    // encontra o ponto do retângulo mais próximo do centro do círculo
    float px, py;

    // eixo x
    if (c->CenterX() < r->Left())
        px = r->Left();
    else
        if (c->CenterX() > r->Right())
            px = r->Right();
        else
            px = c->CenterX();

    // eixo y
    if (c->CenterY() < r->Top())
        py = r->Top();
    else
        if (c->CenterY() > r->Bottom())
            py = r->Bottom();
        else
            py = c->CenterY();

    // verifica se há colisão entre este ponto e o círculo
    Point point(px, py);
    return Collision(&point, c);
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Circle * ca, Circle * cb)
{
    // deltas podem ser negativos se a subtração é feita na ordem errada
    // levando essa possibilidade em conta é melhor pegar os valores absolutos
    float deltaX = abs(ca->CenterX() - cb->CenterX());
    float deltaY = abs(ca->CenterY() - cb->CenterY());

    // calcule a distância entre os centros dos círculos
    float distance = float(sqrt(double(deltaX) * double(deltaX) + double(deltaY) * double(deltaY)));

    // se a distância é menor que a soma dos raios
    // existe colisão entre os círculos
    if (distance <= (ca->radius + cb->radius))
        return true;

    // nenhum colisão detectada
    return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Mixed * m, Geometry * s)
{
    bool collision = false;

    // percorra lista até achar uma colisão
    auto i = m->shapes.begin();

    while (!collision && i != m->shapes.end())
    {
        switch ((*i)->Type())
        {
            // Point
        case POINT_T:
            switch (s->Type())
            {
            case POINT_T:     collision = Collision((Point*)(*i), (Point*)s); break;
            case CIRCLE_T:    collision = Collision((Point*)(*i), (Circle*)s); break;
            case RECTANGLE_T: collision = Collision((Point*)(*i), (Rect*)s);    break;
            case MIXED_T:     collision = Collision((Point*)(*i), (Mixed*)s);    break;
            }
            break;

            // Circle
        case CIRCLE_T:
            switch (s->Type())
            {
            case POINT_T:     collision = Collision((Circle*)(*i), (Point*)s); break;
            case CIRCLE_T:    collision = Collision((Circle*)(*i), (Circle*)s); break;
            case RECTANGLE_T: collision = Collision((Circle*)(*i), (Rect*)s);    break;
            case MIXED_T:     collision = Collision((Circle*)(*i), (Mixed*)s);    break;
            }
            break;

            // Rectangle
        case RECTANGLE_T:
            switch (s->Type())
            {
            case POINT_T:     collision = Collision((Rect*)(*i), (Point*)s); break;
            case CIRCLE_T:    collision = Collision((Rect*)(*i), (Circle*)s); break;
            case RECTANGLE_T: collision = Collision((Rect*)(*i), (Rect*)s);    break;
            case MIXED_T:     collision = Collision((Rect*)(*i), (Mixed*)s);    break;
            }
            break;

            // Mixed
        case MIXED_T:
            collision = Collision((Mixed*)(*i), s);
            break;
        }

        // passa para a próxima geometria da forma mista
        ++i;
    }

    return collision;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Object* oa, Object* ob)
{
    // um dos objetos não tem bounding box
    if (!(oa->BBox() && ob->BBox()))
        return false;

    switch (oa->BBox()->Type())
    {
        // Point    
    case POINT_T:

        switch (ob->BBox()->Type())
        {
        case POINT_T:
            // Point && Point
            return Collision((Point*)oa->BBox(), (Point*)ob->BBox());

        case CIRCLE_T:
            // Point && Circle
            return Collision((Point*)oa->BBox(), (Circle*)ob->BBox());

        case RECTANGLE_T:
            // Point && Rectangle
            return Collision((Point*)oa->BBox(), (Rect*)ob->BBox());

        case MIXED_T:
            // Point && Mixed
            return Collision(oa->BBox(), (Mixed*)ob->BBox());

        default:
            // Point && Unknown
            return false;
        }

        // Circle    
    case CIRCLE_T:

        switch (ob->BBox()->Type())
        {
        case POINT_T:
            // Circle && Point
            return Collision((Circle*)oa->BBox(), (Point*)ob->BBox());

        case CIRCLE_T:
            // Circle && Circle
            return Collision((Circle*)oa->BBox(), (Circle*)ob->BBox());

        case RECTANGLE_T:
            // Circle && Rectangle
            return Collision((Circle*)oa->BBox(), (Rect*)ob->BBox());

        case MIXED_T:
            // Circle && Mixed
            return Collision(oa->BBox(), (Mixed*)ob->BBox());

        default:
            // Circle && Unknown
            return false;
        }

        // Rectangle
    case RECTANGLE_T:

        switch (ob->BBox()->Type())
        {
        case POINT_T:
            // Rectangle && Point
            return Collision((Rect*)oa->BBox(), (Point*)ob->BBox());

        case CIRCLE_T:
            // Rectangle && Circle
            return Collision((Rect*)oa->BBox(), (Circle*)ob->BBox());

        case RECTANGLE_T:
            // Rectangle && Rectangle
            return Collision((Rect*)oa->BBox(), (Rect*)ob->BBox());

        case MIXED_T:
            // Rectangle && Mixed
            return Collision(oa->BBox(), (Mixed*)ob->BBox());

        default:
            // Rectangle && Unknown
            return false;
        }

        // Mixed
    case MIXED_T:
        // Mixed && Geometry
        return Collision((Mixed*)oa->BBox(), ob->BBox());


        // Unknown
    default:
        return false;
    }
}

// ---------------------------------------------------------------------------------

void Scene::CollisionDetection()
{
    // iteradores para as listas
    list<Object*>::iterator start, end;

    // limpa lista de colisões
    collisions.clear();

    // -------------------
    // Detecção da colisão
    // -------------------

    // se existe pelo menos dois objetos que se movem, teste a colisão entre eles
    if (moving.size() >= 2)
    {
        // pega iterador para último elemento da lista
        end = moving.end();
        end--;

        // testa colisão entre todos os pares de objetos que se movem
        for (auto i = moving.begin(); i != end; ++i)
        {
            start = i;

            // j inicia no segundo elemento da lista
            for (auto j = ++start; j != moving.end(); ++j)
            {
                if (Collision(*i, *j))
                    collisions.push_back(ObjectPair(*i, *j));
            }
        }
    }

    // testa colisão entre objetos que se movem e objetos estáticos
    for (auto i : moving)
    {
        for (auto j : statics)
        {
            if (Collision(i, j))
                collisions.push_back(ObjectPair(i, j));
        }
    }

    // --------------------
    // Resolução da colisão
    // --------------------

    if (!collisions.empty())
    {
        for (auto [a,b] : collisions)
        {
            a->OnCollision(b);
            b->OnCollision(a);
        }
    }

    ProcessDeleted();
}

// --------------------------------------------------------------------------------
