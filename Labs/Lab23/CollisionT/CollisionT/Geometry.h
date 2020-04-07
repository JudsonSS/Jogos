/**********************************************************************************
// Geometry (Arquivo de Cabeçalho)
//
// Criação:		05 Oct 2007
// Atualização:	25 Jul 2019
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
	float x, y;												// posição da geometria

public:
	float scale;											// escala da geometria
	float rotation;											// rotação da geometria
	uint type;												// tipo da geometria
	
	Geometry();												// construtor
	virtual ~Geometry();									// destrutor

	virtual float X() const { return x; }					// coordenada x da geometria
	virtual float Y() const { return y; }					// coordenada y da geometria
		
	virtual void Translate(float dx, float dy)				// move a geometria pelo delta (dx,dy)
	{ x += dx; y += dy; }

	virtual void Scale(float factor) 						// amplia/reduz geometria por um fator de escala
	{ scale *= factor; }

	virtual void Rotate(float angle) 						// rotaciona geometria por um ângulo
	{ rotation += angle; }

	virtual void MoveTo(float px, float py)					// move a geometria para a posição (px,py)
	{ x = px; y = py; }
};

// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

class Point : public Geometry
{
public:

	Point();												// construtor padrão
	Point(float posX, float posY);							// construtor usando pontos-flutuantes
	Point(int posX, int posY);								// construtor usando inteiros
	
	float Distance(const Point & p) const;					// calcula a distância até outro ponto
};

// --------------------------------------------------------------------------
// Line
// -------------------------------------------------------------------------

class Line : public Geometry
{
public:
	Point a, b;												// linha vai do ponto A ao ponto B
	
	Line();													// construtor padrão
	Line(float x1, float y1, float x2, float y2);			// construtor usando pontos-flutuantes
	Line(Point& pa, Point& pb);								// construtor usando pontos

	void Rotate(float angle);								// rotaciona linha por um ângulo

	float Ax() const { return x + (a.X() * scale); }		// coordenadas do mundo do ponto A eixo x
	float Ay() const { return y + (a.Y() * scale); }		// coordenadas do mundo do ponto A eixo y
	float Bx() const { return x + (b.X() * scale); }		// coordenadas do mundo do ponto B eixo x
	float By() const { return y + (b.Y() * scale); }		// coordenadas do mundo do ponto B eixo y
};

// --------------------------------------------------------------------------
// Rect
// --------------------------------------------------------------------------

class Rect : public Geometry
{
public:
	float left;												// coordenada esquerda do retângulo
	float top;												// coordenada superior do retângulo
	float right;											// coordenada direita do retângulo
	float bottom;											// coordenada inferior do retângulo

	Rect();													// construtor padrão
	Rect(float x1, float y1, float x2, float y2);			// construtor usando pontos-flutuantes
	Rect(Point& a, Point& b);								// construtor usando pontos

	float Left() const   { return x + (left   * scale); }	// coordenadas do mundo do menor valor do eixo x
	float Top() const    { return y + (top    * scale); }	// coordenadas do mundo do menor valor do eixo y
	float Right() const  { return x + (right  * scale); }	// coordenadas do mundo do maior valor do eixo x
	float Bottom() const { return y + (bottom * scale); }	// coordenadas do mundo do maior valor do eixo y
};

// --------------------------------------------------------------------------
// Circle
// --------------------------------------------------------------------------

class Circle : public Geometry
{
public:
	float radius;											// raio do círculo

	Circle();												// construtor padrão
	Circle(float r);										// contrutor com raio

	float Radius() const { return radius * scale; }			// tamanho do raio
	float CenterX() const { return x; }						// coordenadas do mundo do centro (eixo x)
	float CenterY() const { return y; }						// coordenadas do mundo do centro (eixo y)
};

// --------------------------------------------------------------------------
// Poly
// --------------------------------------------------------------------------

class Poly : public Geometry
{
private:
	Circle * bbox;											// bounding box do polígono
	void     BuildBBox();									// cria a bounding box do polígono

public:
	uint      vertexCount;									// número de vértices 
	Point*    vertexList;									// vetor de vértices do polígono

	Poly();													// construtor padrão
	Poly(Point * vList, uint vCount);						// construtor
	Poly(const Poly& p);									// construtor de cópia
	~Poly();												// destructor

	// necessário para tratar o membro tipo ponteiro
	const Poly& operator=(const Poly& p);					// operador de atribuição

	void Translate(float dx, float dy);						// move polígono pelo delta (dx,dy)
	void Scale(float factor); 								// amplia ou reduz geometria por um fator de escala
	void MoveTo(float px, float py);						// move plígono para a posição (px,py)

	Circle * BBox() { return bbox; }						// retorna bounding box do polígono
}; 

// --------------------------------------------------------------------------
// Mixed
// --------------------------------------------------------------------------

class Mixed : public Geometry
{
public:
	list<Geometry*> shapes;									// lista de formas geométricas
	
	Mixed();												// construtor padrão
	~Mixed();												// destructor

	void Insert(Geometry * s);								// insere geometria na lista
	void Remove(Geometry * s);								// remove geometria da lista

	void Translate(float dx, float dy);						// move a geometria pelo delta (dx,dy)
	void Scale(float factor);								// altera escala da geometria
	void MoveTo(float px, float py);						// move a geometria para a posição (px,py)
};

// --------------------------------------------------------------------------

#endif
