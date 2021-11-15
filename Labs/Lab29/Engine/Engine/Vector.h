/**********************************************************************************
// Vector (Arquivo de Cabeçalho)
// 
// Criação:     18 Nov 2011
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Classe para representar um vetor
//
**********************************************************************************/

#ifndef _PROGJOGOS_VECTOR_H_
#define _PROGJOGOS_VECTOR_H_

#ifdef ENGINE_EXPORTS
#define DLL __declspec( dllexport ) 
#else
#define DLL __declspec( dllimport )
#endif

// --------------------------------------------------------------------------------

#include <cmath>

// --------------------------------------------------------------------------------

class DLL Vector
{
private:
    static const double PI;             // constante PI
    float angle;                        // ângulo do vetor com o eixo x
    float magnitude;                    // magnitude do vetor

public:
    Vector();                           // construtor padrão
    Vector(float ang, float mag);       // construtor com ângulo e magnitude

    void Scale(float factor);           // amplia ou reduz vetor por um fator
    void ScaleTo(float value);          // ajusta rotação para valor indicado
    void Rotate(float theta);           // rotaciona vetor por ângulo em graus
    void RotateTo(float value);         // ajusta rotação para valor indicado
    void Add(const Vector& v);          // adiciona vetor recebido por parâmetro
    
    float Angle() const;                // retorna ângulo do vetor
    float Magnitude() const;            // retorna magnitude do vetor
    float XComponent() const;           // retorna componente X do vetor
    float YComponent() const;           // retorna componente Y do vetor
    float Radians() const;              // retorna ângulo em radianos
}; 

// ---------------------------------------------------------------------------------
// Funções Membro Inline

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