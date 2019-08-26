#pragma once
#include "Vector2D.h"

class Info_coche
{
public:
	Info_coche():n(0){}
	~Info_coche();

	Vector2D p;
	Vector2D p_delante;
	float distancia;
	int n;
	float angulo;
	bool dentro;//0->fuera 1->dentro
	bool lado;//0->izquierda 1->derecha
	int n_total;
};

