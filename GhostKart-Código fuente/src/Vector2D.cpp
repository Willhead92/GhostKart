#include "Vector2D.h"

Vector2D::~Vector2D()
{
}

Vector2D Vector2D::unitario()
{
	Vector2D retorno(x, y); //Inicializa retorno con las variables que le hemos asignado, x,y
	float mod = modulo();
	if (mod > 0.000001)
	{
		retorno.x /= mod;
		retorno.y /= mod;
	}
	return retorno;
}


