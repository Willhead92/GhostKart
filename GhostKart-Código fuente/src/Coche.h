#pragma once
#include "stdlib.h"
#include "glut.h"
#include "ETSIDI.h"
#include <iostream> 
#include <string>
#include <math.h>
#include "Info_coche.h"
#include "Circuito_por_puntos.h"
#include "Vector2D.h"

using namespace std;
using ETSIDI::SpriteSequence;

class Coche
{
	friend class Interaccion;
private:
	//Datos Static
	static int control;//Por defecto en 0, marca que coche toma el control en cada momento

	//Datos del coche
	Vector2D pos;
	Vector2D vel;
	Vector2D vel_externa;//Velocidad recibida en la interacción con otros coches
	Vector2D acel;
	float alfa;
	float aceleracion;
	int color_int;//0->rojo 1->amarillo 2->verde 3->azul 4->blanco 5->negro
	float velocidad_avance;	//el máximo será de 30 (m/s) y mínimo de -2(m/s)
	float velocidad_perpendicular; //Se implementará cuando existan interacciones
	float ang_ruedas;	//entre ANG_MIN_RUE y ANG_MAX_RUE
	int aux_volante;
	int giro_anterior;
	float VEL_MAX;

	//Constantes del coche
	float C_ROZAMIENTO;//Cuanto más alto menos tarda en parar 0.2 en pista y 1 fuera
	//const float C_ROZAMIENTO_P = 0.5f;//Cuanto más alto menos tarda en parar
	const float V_MAX = 65.0f;
	const float V_MIN = -10.0f;
	const float A_MAX = 20.0f;
	const float A_MIN = -20.0f;
	const float VEL_GIRO_RUE = 3.0f;//Cada segundo podemos girar 30 grados el volante, así que tardaremos 3 segundos en moverlo de extremo a extremo (para controlarlo más fluido)
	const float ANG_MIN_RUE = -5.0f;
	const float ANG_MAX_RUE = 5.0f;

	//Datos "auxiliares", no hay que hacer nada con ellos
	SpriteSequence sprite_lateral;
	const float d = 2.418, //desface
		x0 = 0.000 - d,		z0 = 0.0,
		x1 = 0.000 - d,		z1 = 1.041,
		x2 = 1.497 - d,		z2 = z1,
		x3 = 2.183 - d,		z3 = 1.485,
		x4 = 3.540 - d,		z4 = z3,
		x5 = 4.511 - d,		z5 = 1.177,
		x6 = 4.836 - d,		z6 = z5,
		x7 =  x6,			z7 = z0,
		x8 =  x0,			z8 = z3,
		x9 =  x6,			z9 = z3,
		x10 = x0,			z10 = 0.25,
		x11 = x6,			z11 = 0.4,
		yn = 0.956;

	const string r = "rojo", g = "verde", y = "amarillo", b = "azul", w = "blanco", k = "negro";
	string color = r, fichero;
	void dibujar();
	//Datos "auxiliares", no hay que hacer nada con ellos

	Info_coche info;
	int n_vueltas;
	int n_acumulado;
	int n_anterior;
	void contar_vueltas();

public:
	Coche(float x = 0, float y = 0, float ang = 0, int col = 0);
	~Coche();
	Vector2D getPos()	 { return pos; }
	float getPosx()		 { return pos.x; }
	float getPosy()		 { return pos.y; }
	float getN_sig();// { return 30; }
	float getAng()		 { return alfa; }
	float getVelAbs()	 { return velocidad_avance; }
	int GetNvueltas()    { return n_vueltas; }
	int GetNacumulado()  { return n_acumulado; }

	bool derrape();
	void setInfo(Info_coche infor);
	bool _dentro;
	void dibuja();//Método para dibujar según los datos de posición y orientación del coche
	void rotar(float x, float y, float ang);
	void setDatos(float x, float y, float ang, int col, float vel, float a_rued);
	void SetPos(float x, float y, float ang);
	void Parar() { velocidad_avance = 0.0f; velocidad_perpendicular = 0.0f; ang_ruedas = 0.0f; vel.x = 0.0f; vel.y = 0.0f; vel_externa.x = 0.0f; vel_externa.x = 0.0f; n_vueltas = 0; n_anterior = info.n; }
	void setColor();
	//float getvalor(char a);
	void mover(int ac, int gir, float t);//a>1 aceleración aumenta   a<1  aceleración disminuye   rueda<0 gira a la izquierda    a_rueda>1 gira a la derecha    t-> tiempo de ciclo
	void acelera(int ac);
	void gira(int gir);
	void mover(float t);

	//Cuando se haga las interacciones se implementará un método para setear la deriva del impacto
	static void setControl(int c)	{ control = c; }
	static int getControl()			{ return control; }
	void setV_MAX(int V)			{ VEL_MAX = V * 10.0f + 20.0f; }
	
};