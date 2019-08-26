#include "Interfaz.h"


Interfaz::Interfaz() : s_velocimetro("imagenes/velocimetro.png")
{
}


Interfaz::~Interfaz()
{
}

void Interfaz::mostrar(ListaCoches &l, int vista)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 24);
	ETSIDI::printxy("POS.                              VUELTA", 30, 550);
	ETSIDI::printxy("       Vel.      km/h", 50, 50);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
	string spos = to_string(l.get_RacePosition());
	string stot = to_string(l.getNelem());
	string svuelta = to_string(l.GetVueltas());
	string texto = "       " + spos + "/" + stot + "                                                      " + svuelta + "/3";
	ETSIDI::printxy(texto.c_str(), 50, 550);
	string svel = to_string((int)((l[Coche::getControl()]->getVelAbs())*3.6f));
	string info = "                  " + svel;
	ETSIDI::printxy(info.c_str(), 50, 50);

	if (l[Coche::getControl()]->_dentro == 0)
	{
		ETSIDI::setTextColor(255, 0, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
		ETSIDI::printxy("                                      WARNING: ¡FUERA DE PISTA!", 50, 50);
		ETSIDI::setTextColor(255, 255, 255);
	}

	glTranslatef(10, 10, 0);
	s_velocimetro.setSize(1300.0f / 10, 1300.0f / 10);
	s_velocimetro.draw();
	glTranslatef(68, 68, 0.1);
	glRotated((135.0 - (l[Coche::getControl()]->getVelAbs()) * 3.6 * 1.14), 0.0, 0.0, 1.0);
	glColor3ub(255, 1, 0.1);
	glBegin(GL_POLYGON);
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 50.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}