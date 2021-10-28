/**********************************************************************************
// Scene (Arquivo de Cabeçalho)
// 
// Criação:     16 Mar 2012
// Atualização: 25 Out 2021
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

#ifndef _PROGJOGOS_SCENE_H_
#define _PROGJOGOS_SCENE_H_

#include "Geometry.h"                           // bounding box dos objetos
#include <list>                                 // lista da biblioteca STL 
using std::list;                                // list sem precisar do std::
using std::pair;                                // pair sem precisar do std::
class Object;                                   // declaração adiantada

// ---------------------------------------------------------------------------------

enum ObjectGroup
{
    STATIC,                                     // não colidem entre si
    MOVING                                      // colidem entre si e com estáticos
};

using ObjectPair = pair<Object*, Object*>;      // par de objetos em colisão
using ObjectDel  = pair<Object*, int>;          // <objeto,tipo> a deletar da cena

// ---------------------------------------------------------------------------------

class Scene
{
private:
    list<Object*> statics;                      // lista de objetos estáticos
    list<Object*> moving;                       // lista de objetos em movimento
    
    list<ObjectPair> collisions;                // lista de pares de objetos em colisão
    list<ObjectDel> toDelete;                   // lista de objetos a deletar da cena

    list<Object*>::iterator its;                // iterador para elemento estático
    list<Object*>::iterator itm;                // iterador para elemento em movimento
    list<Object*>::iterator it;                 // iterador para elemento atual

    int processing = STATIC;                    // indica qual lista de objetos está sendo processada

    bool Collision(Point * p, Point * q);       // colisão entre ponto e ponto
    bool Collision(Point * p, Rect * r);        // colisão entre ponto e retângulo    
    bool Collision(Point * p, Circle * c);      // colisão entre ponto e círculo
    bool Collision(Point * p, Poly * pol);      // colisão entre ponto e polígono

    bool Collision(Rect * ra, Rect * rb);       // colisão entre retângulos
    bool Collision(Rect * r, Point * p);        // colisão entre retângulo e ponto (inline)
    bool Collision(Rect * r, Circle * c);       // colisão entre retângulo e círculo
    bool Collision(Rect* r, Poly* pol);         // colisão entre retângulo e polígono

    bool Collision(Circle * ca, Circle * cb);   // colisão entre círculos
    bool Collision(Circle * c, Point * p);      // colisão entre círculo e ponto (inline)
    bool Collision(Circle * c, Rect * r);       // colisão entre círculo e retângulo (inline)
    bool Collision(Circle * c, Poly * pol);     // colisão entre círculo e polígono

    bool Collision(Poly* pa, Poly* pb);         // colisão entre polígonos
    bool Collision(Poly* pol, Point* p);        // colisão entre polígono e ponto (inline)
    bool Collision(Poly* pol, Rect* r);         // colisão entre polígono e retângulo (inline)
    bool Collision(Poly* pol, Circle* c);       // colisão entre polígono e círculo (inline)

    bool Collision(Mixed * m, Geometry * s);    // colisão entre geometria mista e uma forma qualquer
    bool Collision(Geometry * s, Mixed * m);    // colisão entre geometria mista e uma forma qualquer (inline)

    void ProcessDeleted();                      // apaga elementos marcados para exclusão
    
public:
    Scene();                                    // construtor
    ~Scene();                                   // destrutor da cena

    void Add(Object * obj, int type);           // adiciona objeto na lista STATIC ou MOVING da cena
    void Remove(Object* obj, int type);         // remove objeto da cena sem deletar
    void Remove();                              // remove objeto sendo processado na cena sem deletar
    void Delete(Object * obj, int type);        // deleta objeto da lista indicada (STATIC ou MOVING)
    void Delete();                              // deleta o objeto cujo Update/Draw está sendo executado
    uint Size();                                // retorna a quantidade de objetos na cena

    void Begin();                               // inicia percurso na lista de objetos
    Object * Next();                            // retorna próximo objeto da lista

    void Update();                              // atualiza todos os objetos da cena
    void Draw();                                // desenha todos os objetos da cena
    void DrawBBox();                            // desenha a bounding box dos objetos na cena

    bool Collision(Object * oa, Object * ob);   // verifica se há colisão entre dois objetos
    void CollisionDetection();                  // trata a colisão entre objetos da cena
};

// --------------------------------------------------------------------------------
// Funções Membro Inline

// colisão entre retângulo e ponto
inline bool Scene::Collision(Rect* r, Point* p)
{ return Collision(p, r); }

// colisão entre círculo e ponto
inline bool Scene::Collision(Circle* c, Point* p)
{ return Collision(p, c); }

// colisão entre círculo e retângulo
inline bool Scene::Collision(Circle* c, Rect* r)
{     return Collision(r, c); }

// colisão entre polígono e ponto
inline bool Scene::Collision(Poly* pol, Point* p)
{ return Collision(p, pol); }

// colisão entre polígono e retângulo
inline bool Scene::Collision(Poly* pol, Rect* r)
{ return Collision(r, pol); }

// colisão entre polígono e círculo
inline bool Scene::Collision(Poly* pol, Circle* c)
{ return Collision(c, pol); }

// colisão entre geometria mista e uma forma qualquer
inline bool Scene::Collision(Geometry* s, Mixed* m)
{     return Collision(m, s); }

// ---------------------------------------------------------------------------------

#endif