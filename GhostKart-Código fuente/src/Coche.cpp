#include "Coche.h"
#define PI 3.14159f
//#define ANG_LIM 10.0f
//#define VEL_MAX 50.0f

int Coche::control;

Coche::Coche(float x, float y, float ang, int col) :sprite_lateral("imagenes/Coches/lateral.png", 6),
			pos(x, y), vel(0.0f, 0.0f), vel_externa(0.0f, 0.0f), acel(0.0f, 0.0f), alfa(ang), color_int(col)
{
	float escala = 220;
	sprite_lateral.setSize(6606.0f / (escala * 6.0f), 338.0f / (escala - 5.0f));
	velocidad_avance = 0.0f;
	velocidad_perpendicular = 0.0f;
	ang_ruedas = 0.0f;
	aux_volante = 0;
	aceleracion = 0;
	giro_anterior = 0;
	control = 0;
	n_vueltas = 0;
	if (color_int > 5||color_int < 0) color_int = 0;
	sprite_lateral.setState(color_int, true);
}

Coche::~Coche()
{
}

void Coche::dibujar()
{
	switch (color_int)
	{
	case 0: color = r; break;
	case 1: color = y; break;
	case 2: color = g; break;
	case 3: color = b; break;
	case 4: color = w; break;
	case 5: color = k; break;
	}
	//Frontal
	glEnable(GL_TEXTURE_2D);
	fichero = "imagenes/Coches/coche_" + color + "/frontal.png";
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(fichero.c_str()).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(1, 1); glVertex3f(x10, -yn, z10);
	glTexCoord2d(1, 0); glVertex3f(x1, -yn, z1);
	glTexCoord2d(0, 0); glVertex3f(x1, yn, z1);
	glTexCoord2d(0, 1); glVertex3f(x10, yn, z10);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//Capo
	glEnable(GL_TEXTURE_2D);
	fichero = "imagenes/Coches/coche_" + color + "/capo.png";
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(fichero.c_str()).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(1, 0); glVertex3f(x1, yn, z1);
	glTexCoord2d(0, 0); glVertex3f(x2, yn, z2);
	glTexCoord2d(0, 1); glVertex3f(x2, -yn, z2);
	glTexCoord2d(1, 1); glVertex3f(x1, -yn, z1);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//Luna delantera
	glEnable(GL_TEXTURE_2D);
	fichero = "imagenes/Coches/coche_" + color + "/luna delantera.png";
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(fichero.c_str()).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(1, 0); glVertex3f(x2, yn, z2);
	glTexCoord2d(0, 0); glVertex3f(x3, yn, z3);
	glTexCoord2d(0, 1); glVertex3f(x3, -yn, z3);
	glTexCoord2d(1, 1); glVertex3f(x2, -yn, z2);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//Techo
	glEnable(GL_TEXTURE_2D);
	fichero = "imagenes/Coches/coche_" + color + "/techo.png";
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(fichero.c_str()).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(1, 0); glVertex3f(x3, yn, z3);
	glTexCoord2d(0, 0); glVertex3f(x4, yn, z4);
	glTexCoord2d(0, 1); glVertex3f(x4, -yn, z4);
	glTexCoord2d(1, 1); glVertex3f(x3, -yn, z3);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//Luna trasera
	glEnable(GL_TEXTURE_2D);
	fichero = "imagenes/Coches/coche_" + color + "/luna trasera.png";
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(fichero.c_str()).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(1, 0); glVertex3f(x4, yn, z4);
	glTexCoord2d(0, 0); glVertex3f(x5, yn, z5);
	glTexCoord2d(0, 1); glVertex3f(x5, -yn, z5);
	glTexCoord2d(1, 1); glVertex3f(x4, -yn, z4);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//Maletero
	glEnable(GL_TEXTURE_2D);
	fichero = "imagenes/Coches/coche_" + color + "/maletero.png";
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(fichero.c_str()).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(1, 0); glVertex3f(x5, yn, z5);
	glTexCoord2d(0, 0); glVertex3f(x6, yn, z6);
	glTexCoord2d(0, 1); glVertex3f(x6, -yn, z6);
	glTexCoord2d(1, 1); glVertex3f(x5, -yn, z5);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//Parte trasera
	glEnable(GL_TEXTURE_2D);
	fichero = "imagenes/Coches/coche_" + color + "/parte trasera.png";
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(fichero.c_str()).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 0); glVertex3f(x6, -yn, z6);
	glTexCoord2d(0, 1); glVertex3f(x11, -yn, z11);
	glTexCoord2d(1, 1); glVertex3f(x11, yn, z11);
	glTexCoord2d(1, 0); glVertex3f(x6, yn, z6);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	//Lateral del piloto
	glRotated(90.0, 1.0, 0.0, 0.0);
	sprite_lateral.setCenter(d, 0);
	glPushMatrix();
	glTranslatef(-0.1, 0, yn);
	sprite_lateral.draw();
	glPopMatrix();

	//Lateral del pasajero
	sprite_lateral.setCenter(d, 0);
	glPushMatrix();
	glTranslatef(-0.1, 0, -yn);
	sprite_lateral.draw();
	glPopMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);
}


void Coche::rotar(float x, float y, float ang)
{
	glTranslatef(pos.x, pos.y, 0);
	glRotated(alfa, 0.0, 0.0, 1.0);
	glTranslatef(-x, y, 0);
	glRotated(-ang, 0.0, 0.0, 1.0);
	dibujar();
	pos.x = pos.x - x;
	pos.y = pos.y + y;
	alfa=alfa+ang;
	glRotated(-alfa, 0.0, 0.0, 1.0);
	glTranslatef(-pos.x, -pos.y, 0);
}

void Coche::setDatos(float x, float y, float ang, int col, float vel, float a_rued)
{
	pos.setPos(x, y);
	alfa = ang;
	color_int = col;
	velocidad_avance = vel;
	ang_ruedas = a_rued;
	n_vueltas = 1;
	if (color_int > 5 || color_int < 0) color_int = 0;
	sprite_lateral.setState(color_int, true);

}
void Coche::SetPos(float x, float y, float ang)
{
	pos.setPos(x, y);
	alfa = ang;

}
void Coche::dibuja()
{
	//glDisable(GL_LIGHTING);
	//glTranslatef(info.p_delante.x, info.p_delante.y, 0.0f);
	//glutSolidTeapot(2);
	//glTranslatef(-info.p_delante.x, -info.p_delante.y, 0.0f);
	//glEnable(GL_LIGHTING);
	//Es gracioso para ver a la tetera por delante

	glTranslatef(pos.x, pos.y, 0);
	glRotated(alfa + 180 , 0.0, 0.0, 1.0);
	dibujar();
	glRotated(-alfa - 180, 0.0, 0.0, 1.0);
	glTranslatef(-pos.x, -pos.y, 0);
}

void Coche::mover(int ac, int gir, float t) {
	acelera(ac);
	gira(gir);

	if (info.dentro == 1)C_ROZAMIENTO = 0.2f;
	else C_ROZAMIENTO = 1.5f;

	velocidad_avance = velocidad_avance + aceleracion * t;
	velocidad_avance = velocidad_avance - C_ROZAMIENTO * velocidad_avance *t - 0.1f;
	vel_externa.x = vel_externa.x - C_ROZAMIENTO * 4.0f * vel_externa.x*t;
	vel_externa.y = vel_externa.y - C_ROZAMIENTO * 4.0f * vel_externa.y*t;
	if (vel_externa.modulo() <= 0.5f) { vel_externa.x = 0.0f; vel_externa.y = 0.0f; }

	ang_ruedas = ang_ruedas + aux_volante * VEL_GIRO_RUE * t;//La velocidad a la que movemos el volante depende de una constante y del tiempo

	if (velocidad_avance < 0 && aceleracion >= 0) velocidad_avance = 0.0f;  //
	if (velocidad_avance > V_MAX)aceleracion = 0.0f;//velocidad_avance = V_MAX;
	if (velocidad_avance < V_MIN)aceleracion = 0.0f;//velocidad_avance = V_MIN;
	alfa = alfa + velocidad_avance * t * ang_ruedas;//La velocidad a la que gira el coche depende de su velocidad de avance 
	derrape();
	vel.x = cos((PI / 180.0f)*alfa)*velocidad_avance + cos((PI / 180.0f)*(alfa - 90.0f))*velocidad_perpendicular + vel_externa.x;
	vel.y = sin((PI / 180.0f)*alfa)*velocidad_avance + sin((PI / 180.0f)*(alfa - 90.0f))*velocidad_perpendicular + vel_externa.y;
	acel.x = cos((PI / 180.0f)*alfa)*aceleracion;
	acel.y = sin((PI / 180.0f)*alfa)*aceleracion;
	pos = pos + vel * t + acel * (0.5*t*t);
	contar_vueltas();
}

void Coche::acelera(int ac){
	if (ac < 0)aceleracion = A_MIN;
	if (ac > 0)aceleracion = A_MAX;
	if (ac == 0)aceleracion = 0.0f;
}

void Coche::gira(int gir){
	if (ang_ruedas >= ANG_MIN_RUE && ang_ruedas <= ANG_MAX_RUE && gir != 0) {
		if (gir < 0)aux_volante = 1;
		if (gir > 0)aux_volante = -1;

		if (gir < 0 && ang_ruedas < 0.0f)ang_ruedas = 0.0f;
		if (gir > 0 && ang_ruedas > 0.0f)ang_ruedas = 0.0f;
	}
	if (ang_ruedas <= ANG_MIN_RUE)ang_ruedas = ANG_MIN_RUE;
	if (ang_ruedas >= ANG_MAX_RUE)ang_ruedas = ANG_MAX_RUE;
	if (gir == 0||gir!=giro_anterior) { 
		ang_ruedas = 0.0f;
		aux_volante = 0;
	}
	giro_anterior = gir;
}

bool Coche::derrape() {
	//velocidad_perpendicular = velocidad_avance * ang_ruedas * 0.2f;
	velocidad_perpendicular = velocidad_avance * velocidad_avance * ang_ruedas * 0.004f;//De esta forma es más realista
	if (velocidad_perpendicular < -25 || velocidad_perpendicular > 25) return true;
	else return false;
}

void Coche::mover(float t) {
	int ac=0, gir=0;
	float alfa_now = fmod(alfa, 360.0f);
	if (alfa_now > 180.0f)alfa_now = alfa_now - 360.0f;
	if (alfa_now < 0.0f) { alfa_now = 360.0f + alfa_now; }
	float alfa_prox = (180.0f/PI)*atan2(info.p_delante.y - pos.y, info.p_delante.x - pos.x);
	if (alfa_prox < 0.0f) { alfa_prox = 360.0f + alfa_prox; }

	ac = 1;
	if (abs(alfa_now - alfa_prox) < 180) {
		if (alfa_now > alfa_prox)gir = 1;
		else gir = -1;
	}
	else {
		if (alfa_now > alfa_prox)gir = -1;
		else gir = 1;
	}

	if (velocidad_avance > VEL_MAX)ac = 0;

	mover(ac, gir, t);
}

void Coche::setColor()
{
	color_int++;
	if (color_int > 5) color_int = 0;
	sprite_lateral.setState(color_int, true);
}

void Coche::setInfo(Info_coche infor) {
	info = infor;
	_dentro = info.dentro;
}

float Coche::getN_sig() {
	if (info.distancia > 20.0f)return 10;
	if (info.distancia<20.0f&&info.distancia>4.0f) {
		return -1.25f*info.distancia + 35.0f;
	}
	return 30.0f;
}

void Coche::contar_vueltas() {
	//La salida está en n=150;
	int dif = abs(info.n - n_anterior);

	if ((info.n >= 150 && n_anterior < 150) && dif < 100)
		n_vueltas++;

	else if ((info.n < 150 && n_anterior >= 150) && dif < 100)
		n_vueltas--;

	n_anterior = info.n;
	int n_;
	if (info.n < 150)    n_ = info.n_total -150 + info.n;
	if (info.n >= 150)   n_ = info.n - 150;
	n_acumulado = n_ + (n_vueltas - 1)*info.n_total;
}