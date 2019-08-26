#include "Decoracion.h"


Decoracion::Decoracion(float x, float y) :_x(x), _y(y)
{

}

Decoracion::~Decoracion()
{

}

void Decoracion::dibujar()
{

}

void Decoracion::setPos(float x, float y)
{
	_x = x;
	_y = y;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


Arbol::Arbol(float x, float y) : Decoracion(x,y), s_arbol("imagenes/decoracion/arbol1.png")
{
	float escala = 20;
	s_arbol.setSize(212.0f / escala, 244.0f / escala);
	s_arbol.setCenter(5.8, 0);
}

Arbol::~Arbol()
{

}

void Arbol::dibujar()
{
	int rot = 3;
	glPushMatrix();
	s_arbol.setCenter(5.80, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslatef(_x, -0.6, -_y);
	for (int i = 0; i < rot; i++)
	{
		glRotated(180 / rot, 0.0, 1.0, 0.0);
		s_arbol.draw();
	}
	glPopMatrix();
}

void Arbol::setPos(float x, float y)
{
	Decoracion::setPos(x, y);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


Roca::Roca(float x, float y) : Decoracion(x, y), s_roca("imagenes/decoracion/roca1.png")
{
	float escala = 150;
	s_roca.setSize(900.0f / escala, 500.0f / escala);
	s_roca.setCenter(5.8, 0);
}

Roca::~Roca()
{

}

void Roca::dibujar()
{
	int rot = 2;
	glPushMatrix();
	s_roca.setCenter(3.33, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslatef(_x, -0.6, -_y);
	for (int i = 0; i < rot; i++)
	{
		glRotated(180 / rot, 0.0, 1.0, 0.0);
		s_roca.draw();
	}
	glPopMatrix();
}

void Roca::setPos(float x, float y)
{
	Decoracion::setPos(x, y);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


MH::MH(float x, float y) : Decoracion(x, y), s_mh("imagenes/decoracion/mh.png")
{
	float escala = 1000;
	s_mh.setSize(1346.0f / escala, 2700.0f / escala);
	s_mh.setCenter(5.8, 0);
}

MH::~MH()
{

}

void MH::dibujar()
{
	glPushMatrix();
	s_mh.setCenter(0.847, 0);
	glRotated(90, 1.0, 0.0, 0.0);
	glTranslatef(_x, 0, -_y);
    s_mh.draw();
	glPopMatrix();
}

void MH::setPos(float x, float y)
{
	Decoracion::setPos(x, y);
}