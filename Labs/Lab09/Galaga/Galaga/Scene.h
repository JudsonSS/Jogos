/**********************************************************************************
// Scene (Arquivo de Cabeçalho)
// 
// Criação:     16 Mar 2012
// Atualização: 18 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para gerenciar o cenário do jogo.
//                
//              Um gerenciador de cena é responsável por guardar os objetos 
//              da cena, atualizando-os e desenhando-os de forma mais prática. 
//              Ele pode ser usado também para percorrer a lista de objetos para 
//              realizar algum processamento individual nos objetos.
//
**********************************************************************************/

#ifndef _PROGJOGOS_SCENE_H_
#define _PROGJOGOS_SCENE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include <list>                         // lista da biblioteca SLT 
using std::list;                        // acessa list sem precisar do std::
class Object;                           // declaração avançada

// ---------------------------------------------------------------------------------

class Scene
{
private:
    list <Object*> objects;             // lista de objetos 
    list <Object*>::iterator next;      // iterador para próximo elemento da lista
    list <Object*>::iterator it;        // iterador para elemento atual
    
public:
    Scene();                            // construtor
    ~Scene();                           // destrutor da cena

    void Add(Object * obj);             // adiciona um objeto a lista
    void Update();                      // atualiza todos os objetos da cena
    void Draw();                        // desenha todos os objetos da cena
    
    void Begin();                       // inicia percurso na lista de objetos
    Object * Next();                    // retorna próximo objeto da lista
    void Remove();                      // remove último objeto retornado por Next()
};

// ---------------------------------------------------------------------------------

#endif