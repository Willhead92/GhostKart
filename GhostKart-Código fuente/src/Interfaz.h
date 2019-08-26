#pragma once
#include "Coche.h"
#include "ListaCoches.h"
#include "ETSIDI.h"
#include "glut.h"
#include "string.h"

using namespace std;
using ETSIDI::Sprite;

class Interfaz
{
	Sprite s_velocimetro;
public:
	Interfaz();
	~Interfaz();
	void mostrar(ListaCoches &j, int vista);
};

