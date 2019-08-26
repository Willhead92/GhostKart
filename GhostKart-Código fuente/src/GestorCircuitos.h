#pragma once
#include "Circuito_por_puntos.h"
#include "ETSIDI.h"
#include "Info_coche.h"
#include "Coche.h"
#include "Decoracion.h"
#define arboles 150
#define rocas 50

class GestorCircuitos
{
public:
	GestorCircuitos();
	~GestorCircuitos();
	void GeneraCircuito(int indice);
	void DibujaCircuito(int v=0, float p=-0.1f);
	Vector2D GetCheckpoints(int indice);
	Vector2D GetCircuito(int indice);
	Vector2D GetLateral_1(int indice);
	Vector2D GetLateral_2(int indice);
	Info_coche GetInfo(float x, float y, int ind);
	float GetAngulosCircuito(int indice);
	int GetN_puntos();
	int GetN_checks();

	int n_arboles = arboles;
	int n_rocas = rocas;
	Arbol *lista_arboles[arboles];
	Roca *lista_rocas[rocas];
	MH *pMH[3];
	Info_coche ok_nook;
	
	int GetNarboles() { return n_arboles; }
	int GetNrocas()	  { return n_rocas; }

private:
	
	int n_checks;
	int densidad_de_puntos;
	float anchura;
	Vector2D *checks;
	Circuito_por_puntos *circuito;
	int n_ind;
	int A, B, C;
};




