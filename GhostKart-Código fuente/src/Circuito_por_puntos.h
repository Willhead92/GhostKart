#pragma once
#include "Vector2D.h"
#include "Info_coche.h"
//#include "Coche.h"

class Circuito_por_puntos
{
private:
	int n_checks;
	int densidad_de_puntos;
	int n_tramo;
	float anchura;
	float *pendientes;
	Vector2D *tramo_aux;
	float modulo(Vector2D p1, Vector2D p2);
	void ajusta_n_puntos();
	float pendiente(int indice);
	void ajusta_pendientes();
	void tramo(int indice);
	float corregir_angulo(float angulo);
	void genera_circuito();
	void genera_laterales();
	Vector2D *checkpoints;
	Vector2D *circuito;
	Vector2D *lateral_1;
	Vector2D *lateral_2;
	float *AngulosCircuito;
	int n_puntos;
	Info_coche info;
public:
	Vector2D GetCheckpoints(int indice);
	Vector2D GetCircuito(int indice);
	Vector2D GetLateral_1(int indice);
	Vector2D GetLateral_2(int indice);
	float GetAngulosCircuito(int indice);
	int GetN_puntos();
	Info_coche GetInfo(Vector2D p, int ind);
	Circuito_por_puntos(Vector2D Checks[], int densidad_de_puntos, int n_checks, float anchura);
	~Circuito_por_puntos();
};