#include "GestorCircuitos.h"
#include "Mapas.h"
#include <iostream>//borrar
#include <string>

#define LADOMAX 500
#define ALTURAMAX 200
#define LOSETA 50

GestorCircuitos::GestorCircuitos()
{
	densidad_de_puntos = 1;
	anchura = 8.0f;
	n_checks = 0;
}

GestorCircuitos::~GestorCircuitos()
{

}

void GestorCircuitos::GeneraCircuito(int indice) {//0->mapa_1  1->mapa_1  2->mapa_1  3->rand_1
	if (indice < 0) {
		indice = 0;
	}
	if (indice > 3) {
		indice = 3;
	}
	if (indice == 3) {
		rand_1[4].x = 200.0f;
		rand_1[4].y = 350.0f + float(ETSIDI::lanzaDado(100.0));
		rand_1[5].x = 300.0f;
		rand_1[5].y = 350.0f + float(ETSIDI::lanzaDado(100.0));
		rand_1[6].x = 350.0f + float(ETSIDI::lanzaDado(100.0));
		rand_1[6].y = 300.0f;
		rand_1[7].x = 350.0f + float(ETSIDI::lanzaDado(100.0));
		rand_1[7].y = 200.0f;
		rand_1[8].x = 300.0f;
		rand_1[8].y = 50.0f + float(ETSIDI::lanzaDado(100.0));
		rand_1[9].x = 200.0f;
		rand_1[9].y = 50.0f + float(ETSIDI::lanzaDado(100.0));
		int aux= 4 + ETSIDI::lanzaDado(5);
		rand_1[aux].x = 200.0f + float(ETSIDI::lanzaDado(100.0));
		rand_1[aux].y = 200.0f + float(ETSIDI::lanzaDado(100.0));
	}
		//sizeof(checks) / sizeof(Vector2D);//No se puede saber el tamaño de un array dinámico
		circuito = new Circuito_por_puntos(map[indice].map, densidad_de_puntos, map[indice].num, anchura);
		n_ind = indice;

		A = 1 + ETSIDI::lanzaDado(9);
		B = 1 + ETSIDI::lanzaDado(3);
		C = 1 + ETSIDI::lanzaDado(8);

		//Crear decoracion
		int x = 0, y = 0;
		for (int i = 0; i < n_arboles; i++)
		{
			do
			{
				x = ETSIDI::lanzaDado(490, 10);
				y = ETSIDI::lanzaDado(490, 10);
			} while (GetInfo(x, y, 0).distancia < 15);
			lista_arboles[i] = new Arbol;
			lista_arboles[i]->setPos(x, y);
		}
		for (int i = 0; i < n_rocas; i++)
		{
			do
			{
				x = ETSIDI::lanzaDado(490, 10);
				y = ETSIDI::lanzaDado(490, 10);
			} while (GetInfo(x, y, 0).distancia < 15);
			lista_rocas[i] = new Roca;
			lista_rocas[i]->setPos(x, y);
		}
		do
		{
			x = ETSIDI::lanzaDado(490, 10);
			y = ETSIDI::lanzaDado(490, 10);
		} while (GetInfo(x, y, 0).distancia < 20);
		pMH[1] = new MH;
		pMH[1]->setPos(x, y);
		pMH[2] = new MH;
		pMH[2]->setPos(93.0f, 300.0f);
		pMH[3] = new MH;
		pMH[3]->setPos(107.0f, 300.0f);
}

void GestorCircuitos::DibujaCircuito(int v, float p)
{	
	int n_puntos = circuito->GetN_puntos();
	float l_bloque = 1.0f * anchura;//El coeficiente modifica la "resolución" del circuito
	int n_bloque = l_bloque / densidad_de_puntos;
	int n = n_puntos / n_bloque;

	if (n_ind == 0) { A = 1; B = 1; C = 1; }
	if (n_ind == 1) { A = 2; B = 1; C = 3; }
	if (n_ind == 2) { A = 3; B = 1; C = 4; }

	for (int i = 0; i < LADOMAX / LOSETA; i++)
	{
		for (int j = 0; j < LADOMAX / LOSETA; j++)
		{
			glEnable(GL_TEXTURE_2D);
			string c1 = "imagenes/Suelos/Suelo_", c3 = ".png";
			string c2 = to_string(A);
			c1 = c1 + c2 + c3;
			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(c1.c_str()).id);

			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1); glVertex3f(i*LOSETA, j*LOSETA, p);
			glTexCoord2d(1, 1); glVertex3f(i*LOSETA, (j + 1)*LOSETA, p);
			glTexCoord2d(1, 0); glVertex3f((i + 1)*LOSETA, (j + 1)*LOSETA, p);
			glTexCoord2d(0, 0); glVertex3f((i + 1)*LOSETA, j*LOSETA, p);
			glEnd();
			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
		}
	}
	
	int aux_pared[16] = { LADOMAX,0,0,0, LADOMAX ,LADOMAX ,LADOMAX,0, 0,LADOMAX,LADOMAX,LADOMAX, 0,0,0,LADOMAX };
	for (int i = 0; i < 4; i++) {
		glEnable(GL_TEXTURE_2D);
		string c4 = "imagenes/Backgrounds/Cielo_", c6 = ".png";
		string c5 = to_string(B);
		c4 = c4 + c5 + c6;
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(c4.c_str()).id);

		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex3f(aux_pared[i * 4], aux_pared[i * 4 + 1], p);
		glTexCoord2d(1, 1); glVertex3f(aux_pared[i * 4 + 2], aux_pared[i * 4 + 3], p);
		glTexCoord2d(1, 0); glVertex3f(aux_pared[i * 4 + 2], aux_pared[i * 4 + 3], ALTURAMAX);
		glTexCoord2d(0, 0); glVertex3f(aux_pared[i * 4], aux_pared[i * 4 + 1], ALTURAMAX);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}

	string c7 = "imagenes/Circuitos/Circuito_", c9 = ".png";
	string c8 = to_string(C);
	c7 = c7 + c8 + c9;

	for (int i = 0; i < n; i++) {
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(c7.c_str()).id);

		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex3f(circuito->GetLateral_1(i*n_bloque).x , circuito->GetLateral_1(i*n_bloque).y, 0);
		glTexCoord2d(1, 1); glVertex3f(circuito->GetLateral_2(i*n_bloque).x , circuito->GetLateral_2(i*n_bloque).y, 0);
		glTexCoord2d(1, 0); glVertex3f(circuito->GetLateral_2((i+1)*n_bloque).x, circuito->GetLateral_2((i+1)*n_bloque).y, 0);
		glTexCoord2d(0, 0); glVertex3f(circuito->GetLateral_1((i + 1)*n_bloque).x, circuito->GetLateral_1((i + 1)*n_bloque).y, 0);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(c7.c_str()).id);

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(circuito->GetLateral_1(n*n_bloque).x, circuito->GetLateral_1(n*n_bloque).y, 0);
	glTexCoord2d(1, 1); glVertex3f(circuito->GetLateral_2(n*n_bloque).x, circuito->GetLateral_2(n*n_bloque).y, 0);
	glTexCoord2d(1, 0); glVertex3f(circuito->GetLateral_2(0).x, circuito->GetLateral_2(0).y, 0);
	glTexCoord2d(0, 0); glVertex3f(circuito->GetLateral_1(0).x, circuito->GetLateral_1(0).y, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	for (float i = 92.0f; i < 108.0f; i = i + 1.0f) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/meta.png").id);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex3f(i, 300.0f, 0.1f);
		glTexCoord2d(1, 1); glVertex3f(i, 301.0f, 0.1f);
		glTexCoord2d(1, 0); glVertex3f(i+1.0f, 301.0f, 0.1f);
		glTexCoord2d(0, 0); glVertex3f(i + 1.0f, 300.0f, 0.1f);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}

	//Pintar decoracion
	for (int i = 0; i < n_arboles; i++) lista_arboles[i]->dibujar();
	for (int i = 0; i < n_rocas; i++) lista_rocas[i]->dibujar();
	pMH[1]->dibujar();
	if (v > 2) {
		pMH[2]->dibujar();
		pMH[3]->dibujar();
	}
}

Vector2D GestorCircuitos::GetCheckpoints(int indice) {
	return circuito->GetCheckpoints(indice);
}

Vector2D GestorCircuitos::GetCircuito(int indice) {
	return circuito->GetCircuito(indice);
}

Vector2D GestorCircuitos::GetLateral_1(int indice) {
	return circuito->GetLateral_1(indice);
}

Vector2D GestorCircuitos::GetLateral_2(int indice) {
	return circuito->GetLateral_2(indice);
}

float GestorCircuitos::GetAngulosCircuito(int indice) {
	return circuito->GetAngulosCircuito(indice);
}

int GestorCircuitos::GetN_puntos() {
	return circuito->GetN_puntos();
}

int GestorCircuitos::GetN_checks() {
	return n_checks;
	
}

Info_coche GestorCircuitos::GetInfo(float x, float y, int ind) {
	Vector2D p;
	p.x = x;
	p.y = y;
	return circuito->GetInfo(p,ind);
}