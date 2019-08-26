#pragma once
#include "stdlib.h"
#include "glut.h"
#include "ETSIDI.h"


using namespace std;
using ETSIDI::Sprite;


class Decoracion
{
	friend class Interaccion;
protected:
	float _x, _y;
public:
	Decoracion(float x = 0, float y = 0);
	~Decoracion();
	virtual void dibujar();
	virtual void setPos(float x, float y);
};

class Arbol : public Decoracion
{
private:
	Sprite s_arbol;
public:
	Arbol(float x = 0, float y = 0);
	~Arbol();
	void dibujar();
	void setPos(float x, float y);
};

class Roca : public Decoracion
{
private:
	Sprite s_roca;
public:
	Roca(float x = 0, float y = 0);
	~Roca();
	void dibujar();
	void setPos(float x, float y);
};

class MH : public Decoracion
{
private:
	Sprite s_mh;
public:
	MH(float x = 0, float y = 0);
	~MH();
	void dibujar();
	void setPos(float x, float y);
};