/**********************************************************************************
// Vector (Arquivo de Cabe�alho)
// 
// Cria��o:     18 Nov 2011
// Atualiza��o: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Classe para representar um vetor
//
**********************************************************************************/

#ifndef _PROGJOGOS_VECTOR_H_
#define _PROGJOGOS_VECTOR_H_

// --------------------------------------------------------------------------------

#include <cmath>

// --------------------------------------------------------------------------------

class Vector
{
private:
    static const double PI;             // constante PI
    float angle;                        // �ngulo do vetor com o eixo x
    float magnitude;                    // magnitude do vetor

public:
    Vector();                           // construtor padr�o
    Vector(float ang, float mag);       // construtor com �ngulo e magnitude

    void Scale(float factor);           // amplia ou reduz vetor por um fator
    void ScaleTo(float value);          // ajusta rota��o para valor indicado
    void Rotate(float theta);           // rotaciona vetor por �ngulo em graus
    void RotateTo(float value);         // ajusta rota��o para valor indicado
    void Add(const Vector& v);          // adiciona vetor recebido por par�metro
    
    float Angle() const;                // retorna �ngulo do vetor
    float Magnitude() const;            // retorna magnitude do vetor
    float XComponent() const;           // retorna componente X do vetor
    float YComponent() const;           // retorna componente Y do vetor
    float Radians() const;              // retorna �ngulo em radianos

    // retorna o �ngulo formado pelos pontos (x1,y1) e (x2,y2)
    float Angle(float x1, float y1, float x2, float y2);

    // retorna a dist�ncia entre os pontos (x1,y1) e (x2,y2)
    float Distance(float x1, float y1, float x2, float y2);    
}; 

// ---------------------------------------------------------------------------------
// Fun��es Membro Inline

inline void Vector::ScaleTo(float value)
{ magnitude = value; }

inline void Vector::RotateTo(float value)
{ angle = value; }

inline float Vector::Angle() const
{ return angle; }

inline float Vector::Magnitude() const
{ return magnitude; }

inline float Vector::XComponent() const
{ return magnitude * cos(Radians()); }    

inline float Vector::YComponent() const
{ return magnitude * sin(Radians()); }    

inline float Vector::Radians() const
{ return float(angle * PI / 180.0); }

// ------------------------------------------------------------------------------

#endif