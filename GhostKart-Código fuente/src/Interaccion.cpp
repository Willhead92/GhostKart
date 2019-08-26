#include "Interaccion.h"
#define HITBOX 2.2f
#define PI 3.1415f
#define F_ELASTICIDAD 1.0f
#define LARGO 4.836f
#define ANCHO 1.917f

Interaccion::Interaccion()
{
}


Interaccion::~Interaccion()
{
}

bool Interaccion::colision(Coche &c1, Coche &c2) {
	float alfa1 = (PI / 180.0f)*c1.alfa;
	float alfa2 = (PI / 180.0f)*c2.alfa;

	Vector2D c1a, c1b, c2a, c2b;
	c1a.x = c1.pos.x + 1.5f * cos(alfa1);
	c1a.y = c1.pos.y + 1.5f * sin(alfa1);
	c1b.x = c1.pos.x + 1.5f * cos(alfa1 + PI);
	c1b.y = c1.pos.y + 1.5f * sin(alfa1 + PI);
	c2a.x = c2.pos.x + 1.5f * cos(alfa2);
	c2a.y = c2.pos.y + 1.5f * sin(alfa2);
	c2b.x = c2.pos.x + 1.5f * cos(alfa2 + PI);
	c2b.y = c2.pos.y + 1.5f * sin(alfa2 + PI);

	float distancias[9];

	distancias[0] = (c1a - c2a).modulo();
	distancias[1] = (c1a - c2.pos).modulo();
	distancias[2] = (c1a - c2b).modulo();
	distancias[3] = (c1.pos - c2a).modulo();
	distancias[4] = (c1.pos - c2.pos).modulo();
	distancias[5] = (c1.pos - c2b).modulo();
	distancias[6] = (c1b - c2a).modulo();
	distancias[7] = (c1b - c2.pos).modulo();
	distancias[8] = (c1b - c2b).modulo();
	float distancia = 10.0f;
	for (int i = 0; i < 9; i++) {
		if (distancias[i] < distancia)distancia = distancias[i];
	}
	float dentro = distancia - HITBOX;

	if (dentro < 0.0f) {
		//Es importante cargarse las componentes del derrape para que se vea más acorde a la realidad
		c1.vel.x = cos((PI / 180.0f)*c1.alfa)*c1.velocidad_avance + c1.vel_externa.x;
		c1.vel.y = sin((PI / 180.0f)*c1.alfa)*c1.velocidad_avance + c1.vel_externa.y;
		c2.vel.x = cos((PI / 180.0f)*c2.alfa)*c2.velocidad_avance + c2.vel_externa.x;
		c2.vel.y = sin((PI / 180.0f)*c2.alfa)*c2.velocidad_avance + c2.vel_externa.y;
		//Es importante cargarse las componentes del derrape para que se vea más acorde a la realidad
		Vector2D dif = c2.pos - c1.pos;
		float d = dif.modulo();
		float angd = dif.argumento();
		float v1 = c1.vel.modulo();
		float ang1 = c1.vel.argumento();
		float v2 = c2.vel.modulo();
		float ang2 = c2.vel.argumento();
		Vector2D desp(dentro / 2 * cos(angd), dentro / 2 * sin(angd));
		c1.pos = c1.pos + desp;
		c2.pos = c2.pos - desp;

		angd = angd - (PI / 2.0f);
		float th1 = ang1 - angd;
		float th2 = ang2 - angd;
		float u1x = v1 * cos(th1);
		float u1y = v1 * sin(th1);
		float u2x = v2 * cos(th2);
		float u2y = v2 * sin(th2);
		float v1x = u1x;
		float v2x = u2x;
		float py = u1y + u2y;
		float ey = u1y * u1y + u2y * u2y;
		float a = 2.0f;
		float b = -2 * py;
		float c = py * py - ey;
		float disc = b * b - 4 * a*c;
		if (disc < 0)disc = 0;
		float v2y = (-b + sqrt(disc)) / (2 * a);
		float v1y = py - v2y;
		float modv1, modv2, fi1, fi2;
		modv1 = F_ELASTICIDAD * sqrt(v1x*v1x + v1y * v1y);
		modv2 = F_ELASTICIDAD * sqrt(v2x*v2x + v2y * v2y);
		fi1 = angd + atan2(v1y, v1x);
		fi2 = angd + atan2(v2y, v2x);
		c1.vel_externa.x = modv1 * cos(fi1);
		c1.vel_externa.y = modv1 * sin(fi1);
		c2.vel_externa.x = modv2 * cos(fi2);
		c2.vel_externa.y = modv2 * sin(fi2);

		c1.velocidad_avance = modv1 * cos(fi1 - alfa1);
		c2.velocidad_avance = modv2 * cos(fi2 - alfa2);

		c1.vel_externa.x = c1.vel_externa.x - c1.velocidad_avance * cos(alfa1);
		c1.vel_externa.y = c1.vel_externa.y - c1.velocidad_avance * sin(alfa1);
		c2.vel_externa.x = c2.vel_externa.x - c2.velocidad_avance * cos(alfa2);
		c2.vel_externa.y = c2.vel_externa.y - c2.velocidad_avance * sin(alfa2);

		c1.velocidad_perpendicular = 0.0f;
		c2.velocidad_perpendicular = 0.0f;
		return true;
	}
	return false;
}

bool Interaccion::colision(Coche &c1) {
	if (c1.pos.x < 3.0f) {
		c1.pos.x = 3.0f;
		return true;
	}
	if (c1.pos.x > 497.0f) {
		c1.pos.x = 497.0f;
		return true;
	}
	if (c1.pos.y < 3.0f) {
		c1.pos.y = 3.0f;
		return true;
	}
	if (c1.pos.y > 497.0f) {
		c1.pos.y = 497.0f;
		return true;
	}
	return false;
}

bool Interaccion::colision(Coche &c, Arbol &a) {
	Vector2D dif;
	dif.x = a._x - c.pos.x;
	dif.y = a._y - c.pos.y;
	float dentro = dif.modulo() - 2.0f;
	if (dentro < 0.0f) {
		float angd = dif.argumento();
		Vector2D desp(dentro / cos(angd), dentro / sin(angd));
		c.pos = c.pos + desp;
		c.velocidad_avance = 0.0f;
		c.velocidad_perpendicular = 0.0f;
		c.vel_externa.x = 0.0f;
		c.vel_externa.y = 0.0f;
		return true;
	}
	return false;
}

bool Interaccion::colision(Coche &c, Roca &r) {
	Vector2D dif;
	dif.x = r._x - c.pos.x;
	dif.y = r._y - c.pos.y;
	float dentro = dif.modulo() - 3.5f;
	if (dentro < 0.0f) {
		float angd = dif.argumento();
		Vector2D desp(dentro / cos(angd), dentro / sin(angd));
		c.pos = c.pos + desp;
		c.velocidad_avance = 0.0f;
		c.velocidad_perpendicular = 0.0f;
		c.vel_externa.x = 0.0f;
		c.vel_externa.y = 0.0f;
		return true;
	}
	return false;
}