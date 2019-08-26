#pragma once
#include "Coche.h"
#include "Decoracion.h"
class Interaccion
{
public:
	Interaccion();
	~Interaccion();
	static bool colision(Coche &c1, Coche &c2);
	static bool colision(Coche &c1);
	static bool colision(Coche &c, Arbol &a);
	static bool colision(Coche &c, Roca &r);
};

