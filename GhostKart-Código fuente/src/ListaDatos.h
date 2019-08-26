#pragma once
#include "Vector2D.h"
#include "Coche.h"

struct datos
{
	Vector2D posicion;
	float angulo;
};

class ListaDatos {
	datos* lista;
	int num;
	int MAX;
public:
	ListaDatos() :num(0), MAX(10000), lista(new datos[10000]) {}
	~ListaDatos();
	void operator +=(Coche &c);
	datos operator [](int a) { return lista[a]; }
	void eliminarDatos();
	int getNum() { return num; }
};
