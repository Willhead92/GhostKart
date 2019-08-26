#pragma once
#include "Coche.h"
#include "ListaCoches.h"
#include "glut.h"
#include "string.h"



class Camara
{
private:
	float pos_x, pos_y, pos_z;
	float objetivo_x, objetivo_y, objetivo_z;
	float distancia; //para vista en tercera persona
public:
	//cuando se pasan objetos de grandes clases es más eficiente pasarlos por referencia
	void tercera_persona(Coche &j);
	void primera_persona(Coche &j);
	void vista_aerea(Coche &j);
	void gestion_camara(ListaCoches &l, int vista);
	Camara();
	~Camara();
};