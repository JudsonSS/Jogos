/**********************************************************************************
// Geometry (Arquivo de Cabeçalho)
//
// Criação:		05 Oct 2007
// Atualização:	03 Jun 2019
// Compilador:	Visual C++ 2019
//
// Descrição:	Agrupa a definição de todas as formas geométricas suportadas:
//              ponto, linha, retângulo, círculo, polígono e mista (agrupamento
//              de uma ou mais geometrias)
//
**********************************************************************************/

#ifndef _DESENVJOGOS_GEOMETRY_H_
#define _DESENVJOGOS_GEOMETRY_H_

#include "Types.h"		// tipos da engine
#include <list>			// lista da STL
using std::list;		// usar list sem std::

// ---------------------------------------------------------------------------

// formatos geométricos
enum GeometryTypes
{
	UNKNOWN_T,
	POINT_T,
	LINE_T,
	RECTANGLE_T,
	CIRCLE_T,
	POLYGON_T,
	MIXED_T
};

// ---------------------------------------------------------------------------
// Geometry
// ---------------------------------------------------------------------------

class Geometry
{
protected:
	float x, y;											// posição da geometria

public:
	uint type;											// tipo da geometria
	
	Geometry();											// construtor
	virtual ~Geometry();								// destrutor

	virtual float X() const { return x; }				// coordenada x da geometria
	virtual float Y() const { return y; }				// coordenada y da geometria
		
	virtual void Translate(float dx, float dy)			// move a geometria pelo delta (dx,dy)
	{ x += dx; y += dy; }

	virtual void MoveTo(float px, float py)				// move a geometria para a posição (px,py)
	{ x = px; y = py; }
};

// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

class Point : public Geometry
{
public:

	Point();											// construtor padrão
	Point(float posX, float posY);						// construtor usando pontos-flutuantes
	Point(int posX, int posY);							// construtor usando inteiros
	
	float Distance(const Point & p) const;				// calcula a distância até outro ponto
};

// --------------------------------------------------------------------------
// Line
// -------------------------------------------------------------------------

class Line : public Geometry
{
public:
	Point a, b;											// linha vai do ponto A ao ponto B
	
	Line();												// construtor padrão
	Line(float x1, float y1, float x2, float y2);		// construtor usando pontos-flutuantes
	Line(Point& pa, Point& pb);							// construtor usando pontos

	float Ax() const { return x + a.X(); }				// coordenadas do mundo do ponto A eixo x
	float Ay() const { return y + a.Y(); }				// coordenadas do mundo do ponto A eixo y
	float Bx() const { return x + b.X(); }				// coordenadas do mundo do ponto B eixo x
	float By() const { return y + b.Y(); }				// coordenadas do mundo do ponto B eixo y
};

// --------------------------------------------------------------------------
// Rect
// --------------------------------------------------------------------------

class Rect : public Geometry
{
public:
	float left;											// coordenada esquerda do retângulo
	float top;											// coordenada superior do retângulo
	float right;										// coordenada direita do retângulo
	float bottom;										// coordenada inferior do retângulo

	Rect();												// construtor padrão
	Rect(float x1, float y1, float x2, float y2);		// construtor usando pontos-flutuantes
	Rect(Point& a, Point& b);							// construtor usando pontos

	float Left() const   { return x + left; }			// coordenadas do mundo do menor valor do eixo x
	float Top() const    { return y + top; }			// coordenadas do mundo do menor valor do eixo y
	float Right() const  { return x + right; }			// coordenadas do mundo do maior valor do eixo x
	float Bottom() const { return y + bottom; }			// coordenadas do mundo do maior valor do eixo y
};

// --------------------------------------------------------------------------
// Circle
// --------------------------------------------------------------------------

class Circle : public Geometry
{
public:
	float radius;										// raio do círculo

	Circle();											// construtor padrão
	Circle(float r);									// contrutor com raio

	float CenterX() const { return x; }					// coordenadas do mundo do centro (eixo x)
	float CenterY() const { return y; }					// coordenadas do mundo do centro (eixo y)
};

// --------------------------------------------------------------------------
// Poly
// --------------------------------------------------------------------------

class Poly : public Geometry
{
public:
	uint      vertexCount;								// número de vértices 
	Point*    vertexList;								// vetor de vértices do polígono

	Poly();												// construtor padrão
	Poly(Point * vList, uint vCount);					// construtor
	Poly(const Poly& p);								// construtor de cópia
	~Poly();											// destructor

	// necessário para tratar o membro tipo ponteiro
	const Poly& operator=(const Poly& p);				// operador de atribuição
}; 

// --------------------------------------------------------------------------
// Mixed
// --------------------------------------------------------------------------

class Mixed : public Geometry
{
public:
	list<Geometry*> shapes;								// lista de formas geométricas
	
	Mixed();											// construtor padrão
	~Mixed();											// destructor

	void Insert(Geometry * s);							// insere geometria na lista
	void Remove(Geometry * s);							// remove geometria da lista

	void Translate(float dx, float dy);					// move a geometria pelo delta (dx,dy)
	void MoveTo(float px, float py);					// move a geometria para a posição (px,py)
};

// --------------------------------------------------------------------------

#endif
