#pragma once
#include "Coche.h"
#include "GestorCircuitos.h"
#include "Interaccion.h"
#define MAX_COCHES 10
#define N_VUELTAS 4
#define VUELTAS_MODO_F 2

class ListaCoches
{
private:
	Coche* lista[MAX_COCHES];
	int nElem;
	int race_position;

public:
	ListaCoches();
	~ListaCoches();
	bool agregar(Coche *c);
	void dibuja();
	void mover(int ac, int gir, float t);
	void eliminar(int index);
	void eliminarLista();
	Coche* operator [](int);
	int getNelem() { return nElem; }
	void setInfo(GestorCircuitos circ);
	
	void vistaGaraje();
	void parrillaSalida();
	void SetV_MAX(int V);
	void rebote(bool aux);
	void limites();
	void Calcula_Posicion();
	int GetVueltas();
	int get_RacePosition() { return race_position; }

};

