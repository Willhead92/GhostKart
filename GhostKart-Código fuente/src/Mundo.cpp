#include "Mundo.h"
#include "glut.h"
#include <math.h>
#include "Vector2D.h"


Mundo::Mundo() : s_velocimetro("imagenes/velocimetro.png"), coche_fantasma(0,0,0,4)
{
	isDownpress = false;
	isUppress = false;
	isRightpress = false;
	isLeftpress = false;
	cambiar_vista = 0;
	n_enemigos = 4;
	nivel = 3;
	circuito.GeneraCircuito(0);//Circuito por defecto 
	Coche *c0 = new Coche(100.0f, 200.0f, 90.0f, 0);
	coches.agregar(c0);
	fantasma = false;
	counter = 0;
}

void Mundo::Dibuja()
{
	camara.gestion_camara(coches, cambiar_vista);
	circuito.DibujaCircuito(coches.GetVueltas());
	coches.setInfo(circuito);
	coches.dibuja();
	if(fantasma) coche_fantasma.dibuja();
	DibujaMarcadores(coches);
	derrape = coches[Coche::getControl()]->derrape();
}

void Mundo::Mueve()
{
	int av = 0, gir = 0;

	if (isUppress)  av = 1;
	else			av = 0;

	if (isLeftpress)  gir = -1;

	if (isRightpress)  gir = 1;

	if (isUppress == false && isDownpress == false) av = 0;

	if (isRightpress == false && isLeftpress == false)  gir = 0;

	if (isDownpress)  av = -1;
	
	coches.mover(av, gir, 0.025f);
	coches.rebote(cambiar_coche);
	coches.limites();
	coches.Calcula_Posicion();

	if (!n_enemigos && !fantasma && coches[0]->GetNvueltas()<VUELTAS_MODO_F ) datos += GetCoche();

	if (fantasma && counter<datos.getNum() ) {
		coche_fantasma.SetPos(datos[counter].posicion.x, datos[counter].posicion.y, datos[counter].angulo);
		counter++;
	}

	for (int i = 0; i < circuito.GetNarboles(); i++) 
		Interaccion::colision(*coches[Coche::getControl()], *circuito.lista_arboles[i]);
	
	for (int i = 0; i < circuito.GetNrocas(); i++) 
		Interaccion::colision(*coches[Coche::getControl()], *circuito.lista_rocas[i]);
}

void Mundo::Inicializa()
{
	counter = 0;
	cambiar_vista = 0;
	if (!n_enemigos && !fantasma) datos.eliminarDatos();
	Coche::setControl(0);
	coches.eliminarLista();
	for (int i = 0; i < n_enemigos; i++) {
		Coche *c= new Coche(0.0f, 0.0f, 0.0f, ETSIDI::lanzaDado(7)-1);
		coches.agregar(c);
	}
	coches.SetV_MAX(nivel);
	coches.parrillaSalida();
}

void Mundo::TeclaDown_mundo(unsigned char key)
{
	switch (key)
	{
	case 'w': isUppress = true; break;
	case 's': isDownpress = true; break;
	case 'a': isLeftpress = true; break;
	case 'd': isRightpress = true; break;
	case ' ': cambiar_coche = true; break;

	case 'k':
		cambiar_vista++;
		if (cambiar_vista > 2)
			cambiar_vista = 0;
		break;
	}
}

void Mundo::TeclaDown_mundo_especial(unsigned char key) {
	switch (key)
	{
	case GLUT_KEY_UP: isUppress = true; break;
	case GLUT_KEY_DOWN: isDownpress = true; break;
	case GLUT_KEY_LEFT: isLeftpress = true; break;
	case GLUT_KEY_RIGHT: isRightpress = true; break;
	}
}

void Mundo::TeclaUp_mundo(unsigned char key)
{
	switch (key)
	{
	case 'w': isUppress = false; break;
	case 's': isDownpress = false; break;
	case 'a': isLeftpress = false; break;
	case 'd': isRightpress = false; break;
	case ' ': cambiar_coche = false; break;
	}
}

void Mundo::TeclaUp_mundo_especial(unsigned char key) {
	switch (key)
	{
	case GLUT_KEY_UP: isUppress = false; break;
	case GLUT_KEY_DOWN: isDownpress = false; break;
	case GLUT_KEY_LEFT: isLeftpress = false; break;
	case GLUT_KEY_RIGHT: isRightpress = false; break;
	}
}

void Mundo::dibuja_circuito(int v, float p) {
	circuito.DibujaCircuito(v, p);
}

void Mundo::genera_circuito(int n) {
	circuito.GeneraCircuito(n);
}

void Mundo::enemigos(bool i) {
	if (i == 0 && n_enemigos>0) {
		n_enemigos--;
	}
	if (i == 1 && n_enemigos<10) {
		n_enemigos++;
	}
}

void Mundo::set_nivel(bool i) {
	if (i == 0 && nivel > 1) {
		nivel--;
	}
	if (i == 1 && nivel < 4) {
		nivel++;
	}
}

void Mundo::DibujaMarcadores(ListaCoches &lista) 
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
	string spos = to_string(lista.get_RacePosition());
	string stot = to_string(lista.getNelem());
	string svuelta = to_string(lista.GetVueltas());

	string vuelta_final = n_enemigos ? "/3" : "/1";

	string texto = "       " + spos + "/" + stot + "                                                      " + svuelta + vuelta_final;
	ETSIDI::printxy(texto.c_str(), 50, 550);
	string svel = to_string((int)((lista[Coche::getControl()]->getVelAbs())*3.6f));
	string info = "                  " + svel;
	ETSIDI::printxy(info.c_str(), 50, 50);

	if (lista[Coche::getControl()]->_dentro == 0)
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
	glRotated((135.0 - (lista[Coche::getControl()]->getVelAbs()) * 3.6 * 1.14), 0.0, 0.0, 1.0);
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





