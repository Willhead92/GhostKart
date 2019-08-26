#include "Coche.h"
#include "ListaCoches.h"
#include "Camara.h"
#include "ETSIDI.h"
#include "GestorCircuitos.h"
#include "ListaDatos.h"

#define PI 3.141592
#define N_VUELTAS 4
#define VUELTAS_MODO_F 2

using namespace std;
using ETSIDI::Sprite;

class Mundo
{
private:
	Sprite s_velocimetro;
	Camara camara;
	Coche coche_fantasma;
	ListaCoches coches;
	ListaDatos datos;
	GestorCircuitos circuito;

	bool isDownpress;
	bool isUppress;
	bool isRightpress;
	bool isLeftpress;
	bool cambiar_coche;
	bool derrape = false;
	int cambiar_vista;//con la misma tecla cambia entre primera, segunda persona y vista aérea
	int n_enemigos;//Por defecto a 4
	int nivel;//Por defecto a 5
	bool fantasma; //bandera que indica si está activo el modo corredor fantasma
	int counter;

public: 

	Mundo();

	void TeclaDown_mundo(unsigned char key);
	void TeclaUp_mundo(unsigned char key);
	void TeclaDown_mundo_especial(unsigned char key);//
	void TeclaUp_mundo_especial(unsigned char key);//

	Coche& GetCoche()		{ return *coches[Coche::getControl()]; }
	int get_n_enemigos()	{ return n_enemigos; }
	int get_nivel()			{ return nivel; }
	bool &Fantasma()		{ return fantasma; } // funciona como Rvalue y Lvalue
	bool getKeyW()			{ return isUppress; }
	bool derrape_ext()		{ return derrape; }
	int Get_Race_Position() { return coches.get_RacePosition(); }
	int CambiarVista()		{ return cambiar_vista; }
	void vistagaraje()		{ coches.vistaGaraje(); }

	void Inicializa(); 
	void Mueve();
	void Dibuja();
	void DibujaMarcadores(ListaCoches &lista);
	void set_nivel(bool i);

	void dibuja_circuito(int v=0, float p=-0.1f);
	void genera_circuito(int n);
	void enemigos(bool i);
	
};
