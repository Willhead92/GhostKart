#pragma once
#include "Mundo.h"

using ETSIDI::Sprite;


class Coordinador
{
protected:

	enum Estado { INICIO, PERSONALIZAR, CIRCUITO, JUEGO, PAUSA, COMIENZO, FIN, FIN_FANTASMA, INSTRUCCIONES};
	Estado estado;
	Sprite nombre_juego;
	Mundo mundo;


public:
	Coordinador();
	virtual~Coordinador();

	void tecla_up(unsigned char key);
	void tecla_down(unsigned char key);
	void tecla_up_especial(unsigned char key);
	void tecla_down_especial(unsigned char key);
	void mueve();
	void dibuja();

private:
	int cuenta_atras;
	bool flagw = true;
	bool flagd = false;
};

