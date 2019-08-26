#include "Circuito_por_puntos.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159f
#define N_SUMA 5;

Circuito_por_puntos::Circuito_por_puntos(Vector2D checks[], int densidad_de_puntos, int n_checks, float anchura)
{
	this->n_checks = n_checks;
	this->densidad_de_puntos = densidad_de_puntos;
	this->anchura = anchura;
	checkpoints = new Vector2D[n_checks];

	for (int i = 0; i < n_checks; i++) 
		checkpoints[i] = checks[i];
	
	//checkpoints = checks;
	pendientes = new float[n_checks];
	ajusta_pendientes();
	ajusta_n_puntos();
	n_tramo = 0;
	circuito = new Vector2D[n_puntos];
	lateral_1 = new Vector2D[n_puntos];
	lateral_2 = new Vector2D[n_puntos];
	AngulosCircuito = new float[n_puntos];
	genera_circuito();
	genera_laterales();
}

Circuito_por_puntos::~Circuito_por_puntos()
{
	delete[] checkpoints;//Da un error por alguna razón
	delete[] circuito;
	delete[] pendientes;
	delete[] lateral_1;
	delete[] lateral_2;
	delete[] AngulosCircuito;
}

void Circuito_por_puntos::genera_laterales() {
	int c_i, c_f;
	float x_origen;
	float y_origen;
	float x_siguiente;
	float y_siguiente;
	float x_girar;
	float y_girar;
	float ang;
	for (int i = 0; i < n_puntos; i++) {
		c_i = i;
		c_f = c_i + 1;
		if (c_i == n_puntos - 1) { c_i = n_puntos - 1; c_f = 0; }
		x_origen = circuito[c_i].x;
		y_origen = circuito[c_i].y;
		x_siguiente = circuito[c_f].x;
		y_siguiente = circuito[c_f].y;
		ang = atan2(y_siguiente - y_origen, x_siguiente - x_origen);
		AngulosCircuito[i] = ang;
		//printf("%d %f\n", i, ang);
		//printf("x_origen: %f y_origen: %f x_siguiente: %f y_siguiente: %f\n", x_origen, y_origen, x_siguiente, y_siguiente);
		x_girar = x_origen + cos(ang)*anchura;
		y_girar = y_origen + sin(ang)*anchura;
		lateral_1[c_i].x = ((x_girar - x_origen) * cos(PI / 2.0f)) - ((y_origen - y_girar) * sin(PI / 2.0f)) + x_origen;
		lateral_2[c_i].x = ((x_girar - x_origen) * cos(-PI / 2.0f)) - ((y_origen - y_girar) * sin(-PI / 2.0f)) + x_origen;
		lateral_1[c_i].y = ((y_origen - y_girar) * cos(PI / 2.0f)) - ((x_girar - x_origen) * sin(PI / 2.0f)) + y_origen;
		lateral_2[c_i].y = ((y_origen - y_girar) * cos(-PI / 2.0f)) - ((x_girar - x_origen) * sin(-PI / 2.0f)) + y_origen;
	}
}

void Circuito_por_puntos::genera_circuito() {
	int c_i = 0;
	int c_f = 0;
	int c = 0;
	for (int i = 0; i < n_checks; i++) {
		tramo(i);
		c_i = c_f;
		c_f = c_f + n_tramo;
		c = 0;
		for (int j = c_i; j < c_f; j++) {
			circuito[j].x = tramo_aux[c].x;
			circuito[j].y = tramo_aux[c].y;
			c++;
		}
		delete[] tramo_aux;
	}
}

void Circuito_por_puntos::tramo(int indice) {
	if (indice < 0)indice = 0;
	if (indice > n_checks - 1)indice = n_checks - 1;
	int pi = indice;
	int pf = indice + 1;
	if (indice == n_checks - 1) pf = 0;
	/*Datos*/
	float mod = modulo(checkpoints[pi], checkpoints[pf]);
	float angulo = atan2(checkpoints[pf].y - checkpoints[pi].y, checkpoints[pf].x - checkpoints[pi].x);
	float pend_i = tan(corregir_angulo(pendientes[pi] - angulo));
	float pend_f = tan(corregir_angulo(pendientes[pf] - angulo));
	float xi = checkpoints[pi].x;
	float yi = checkpoints[pi].y;
	float xf = checkpoints[pf].x;
	float yf = checkpoints[pf].y;
	int n_puntos_tramo = densidad_de_puntos * mod;
	n_tramo = n_puntos_tramo;
	float dx = mod / n_puntos_tramo;
	/*Datos*/
	tramo_aux = new Vector2D[n_puntos_tramo];
	float a, b, c = pend_i, d = 0.0f;
	b = (-pend_f - 2 * pend_i) / mod;
	a = (pend_i + pend_f) / (mod*mod);
	for (int i = 0; i < n_puntos_tramo; i++) {
		tramo_aux[i].x = i * dx;
		tramo_aux[i].y = a * tramo_aux[i].x*tramo_aux[i].x*tramo_aux[i].x + b * tramo_aux[i].x*tramo_aux[i].x + c * tramo_aux[i].x + d;
	}
	//Traslado de coordenadas
	for (int i = 0; i < n_puntos_tramo; i++) {
		float x = xi + tramo_aux[i].x*cos(angulo) - tramo_aux[i].y*sin(angulo);
		float y = yi + tramo_aux[i].x*sin(angulo) + tramo_aux[i].y*cos(angulo);
		tramo_aux[i].x = x;
		tramo_aux[i].y = y;

	}
}

float Circuito_por_puntos::corregir_angulo(float angulo) {
	float ang = fmod(angulo, 2 * PI);
	if (ang < (-1 * PI))ang = 2 * PI + ang;
	else if (ang > PI)ang = ang - 2 * PI;
	return ang;
}

void Circuito_por_puntos::ajusta_pendientes() {
	for (int i = 0; i < n_checks; i++) {
		pendientes[i] = pendiente(i);
	}
}

//Empleando bisectriz

float Circuito_por_puntos::pendiente(int indice) {
	if (indice < 0)indice = 0;
	if (indice > n_checks - 1)indice = n_checks - 1;
	int pi = indice - 1;
	int pf = indice + 1;
	if (indice == 0) pi = n_checks - 1;
	if (indice == n_checks - 1) pf = 0;
	float ang1 = atan2(checkpoints[pf].y - checkpoints[indice].y, checkpoints[pf].x - checkpoints[indice].x);
	float ang2 = atan2(checkpoints[pi].y - checkpoints[indice].y, checkpoints[pi].x - checkpoints[indice].x);
	float ang = (ang1 + ang2) / 2.0f;
	float angmas90 = ang + PI / 2.0f;
	if (fabs(angmas90 - ang1) < PI / 2.0f) { ang = angmas90; }
	else ang = angmas90 - PI;
	return ang;//ojo a los radianes
}

float Circuito_por_puntos::modulo(Vector2D p1, Vector2D p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

void Circuito_por_puntos::ajusta_n_puntos() {
	n_puntos = 0;
	for (int i = 0; i < n_checks - 1; i++) {
		n_puntos += densidad_de_puntos * modulo(checkpoints[i], checkpoints[i + 1]);
	}
	n_puntos += densidad_de_puntos * modulo(checkpoints[0], checkpoints[n_checks - 1]);
}

Vector2D Circuito_por_puntos::GetCheckpoints(int indice) {
	if (indice < 0)indice = 0;
	if (indice > n_checks - 1)indice = n_checks - 1;
	return checkpoints[indice];
}

Vector2D Circuito_por_puntos::GetCircuito(int indice) {
	if (indice < 0)indice = 0;
	if (indice > n_puntos - 1)indice = indice - n_puntos;
	return circuito[indice];
}

Vector2D Circuito_por_puntos::GetLateral_1(int indice) {
	if (indice < 0)indice = 0;
	if (indice > n_puntos - 1)indice = n_puntos - 1;
	return lateral_1[indice];
}

Vector2D Circuito_por_puntos::GetLateral_2(int indice) {
	if (indice < 0)indice = 0;
	if (indice > n_puntos - 1)indice = n_puntos - 1;
	return lateral_2[indice];
}

float Circuito_por_puntos::GetAngulosCircuito(int indice) {
	if (indice < 0)indice = 0;
	if (indice > n_puntos - 1)indice = n_puntos - 1;
	return AngulosCircuito[indice];
}

int Circuito_por_puntos::GetN_puntos() {
	return n_puntos;
}

Info_coche Circuito_por_puntos::GetInfo(Vector2D p, int ind) {
	float d = modulo(p, circuito[0]), d_aux;
	int n = 0;
	for (int i = 0; i < n_puntos; i++) {
		d_aux = modulo(p, circuito[i]);
		if (d_aux < d) { 
			d = d_aux;
			n = i;
		}
	}
	info.distancia = d;
	info.n = n;
	info.p = circuito[n];
	info.angulo = AngulosCircuito[n];
	float l1_aux = modulo(p, lateral_1[n]);
	float l2_aux = modulo(p, lateral_2[n]);
	if (l1_aux < l2_aux)info.lado = 1;
	else info.lado = 0;
	if (d < anchura) { info.dentro = 1; }
	else info.dentro = 0;
	info.n_total = n_puntos;
	int c = n + ind;
	if (c > n_puntos-1) c = c - n_puntos;
	info.p_delante = circuito[c];
	return info;
}
