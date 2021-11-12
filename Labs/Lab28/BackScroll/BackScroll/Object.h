/**********************************************************************************
// Object (Arquivo de Cabeçalho)
//
// Criação:     01 Out 2007
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Essa é a classe base para todos objetos do jogo.
//
//              Um objeto do jogo é qualquer coisa que possámos querer desenhar
//              ou interagir dentro do jogo. Por exemplo, um soldado, um prédio,
//              um projétil, uma forma geométrica, etc.
//
**********************************************************************************/

#ifndef _PROGJOGOS_OBJECT_H_
#define _PROGJOGOS_OBJECT_H_

// -----------------------------------------------------------------------------

#include "Types.h"                              // usando os tipos personalizados da engine
#include "Game.h"                               // representação de um jogo
#include "Window.h"                             // janela usada para o jogo
#include "Geometry.h"                           // todo objeto deve ter uma bounding box

// -----------------------------------------------------------------------------

class Object
{
private:
    float posX, posY, posZ;                     // coordenadas (x,y,z)
    float scaleFactor;                          // fator de escala
    float rotationAngle;                        // ângulo de rotação
    Geometry* bbox;                             // bounding box

protected:
    static Window* & window;                    // janela do jogo
    static Game* & game;                        // jogo em execução
    static float & gameTime;                    // tempo do último quadro

    const float & x = posX;                     // coordenada x do objeto
    const float & y = posY;                     // coordenada y do objeto
    const float & z = posZ;                     // coordenada z do objeto
    const float & scale = scaleFactor;          // valor da escala do objeto
    const float & rotation = rotationAngle;     // valor da rotação do objeto

    uint type;                                  // tipo do objeto

public:
    Object();                                   // construtor
    virtual ~Object();                          // destrutor virtual

    // ------------------------------------------------
    // funções virtuais    
    // ------------------------------------------------
    // podem ser sobrescritas na classe derivada
    // e chamadas corretamente mesmo usando um
    // ponteiro para a classe base

    // retorna coordenada x do objeto
    virtual float X() const;

    // retorna coordenada y do objeto
    virtual float Y() const;

    // retorna coordenada z do objeto
    virtual float Z() const;

    // retorna escala do objeto
    virtual float Scale() const;

    // retorna rotação do objeto
    virtual float Rotation() const;

    // retorna tipo do objeto
    virtual uint Type() const;

    // muda a bounding box do objeto
    virtual void BBox(Geometry* bb);

    // retorna a bounding box do objeto
    virtual Geometry* BBox() const;

    // move o objeto por (dx, dy, dz)
    virtual void Translate(float dx, float dy, float dz = 0.0f);

    // move o objeto para as coordenadas (px, py, pz)
    virtual void MoveTo(float px, float py, float pz);

    // move o objeto para as coordenadas (px, py)
    virtual void MoveTo(float px, float py);

    // amplia ou reduz objeto pelo fator
    virtual void Scale(float factor);

    // ajusta escala para novo valor
    virtual void ScaleTo(float value);

    // rotaciona geometria por um ângulo
    virtual void Rotate(float angle);

    // ajusta a rotação para novo valor
    virtual void RotateTo(float value);

    // faz a resolução de colisão do objeto
    virtual void OnCollision(Object* obj);

    // ------------------------------------------------
    // funções virtuais pura    
    // ------------------------------------------------    
    // devem ser sobrescritas na classe derivada
    // fazem com que a classe seja abstrata

    // atualiza estado do objeto
    virtual void Update() = 0;

    // desenha o objeto na tela
    virtual void Draw() = 0;
};

// -----------------------------------------------------------------------------
// Métodos Inline

// retorna coordenada x do objeto
inline float Object::X() const
{ return posX; }

// retorna coordenada y do objeto
inline float Object::Y() const
{ return posY; }

// retorna coordenada z do objeto
inline float Object::Z() const
{ return posY; }

// retorna a escala do objeto
inline float Object::Scale() const
{ return scaleFactor; }

// retorna a rotação do objeto
inline float Object::Rotation() const
{ return rotationAngle; }

// retorna tipo do objeto
inline uint Object::Type() const
{ return type; }

// retorna a bounding box do objeto
inline Geometry* Object::BBox() const
{ return bbox; }

// -----------------------------------------------------------------------------

#endif


