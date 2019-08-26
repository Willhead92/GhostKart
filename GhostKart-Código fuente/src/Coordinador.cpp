#include "Coordinador.h"
#include<string>
#include <chrono>
#define N_VUELTAS 4
#define VUELTAS_MODO_F 2 

Coordinador::Coordinador() :nombre_juego("imagenes/ghostkart_Logo.png", 1)
{
	float escala = 40;
	nombre_juego.setSize(441 / escala, 224 / escala);
	ETSIDI::playMusica("musica/Back_in_Black.mp3", true);
	estado = INICIO;
	cuenta_atras = 0;
}


Coordinador::~Coordinador()
{

}

void Coordinador::dibuja()
{
	
	if (estado == INICIO)
	{
		gluLookAt  (0.0, 7.5, 30.0, 
					0.0, 7.5, 0.0,  
					0.0, 1.0, 0.0); 

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Fondo_inicio.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(1, 1); glVertex3f(-15, -4, -0.1);
		glTexCoord2d(1, 0); glVertex3f(-15, 20, -0.1);
		glTexCoord2d(0, 0); glVertex3f(15, 20, -0.1);
		glTexCoord2d(0, 1); glVertex3f(15, -4, -0.1);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
		ETSIDI::printxy("PULSE LA TECLA: -E- PARA EMPEZAR A JUGAR", -9, 1);
		ETSIDI::printxy("                 -P- PARA PERSONALIZAR EL COCHE", -8, 0);
		ETSIDI::printxy("                 -C- PARA MODIFICAR EL CIRCUITO", -8, -1);
		ETSIDI::printxy("                 -I-  PARA LEER LAS INSTRUCCIONES", -8, -2);
		ETSIDI::printxy("                 -S- PARA SALIR DEL JUEGO", -8, -3);
		if (mundo.get_n_enemigos() == 0)
			ETSIDI::printxy("CORREDOR FANTASMA", -11, 4);

		string c1 = "RIVALES: ";
		string c2 = to_string(mundo.get_n_enemigos());
		string c3 = c1 + c2;
		ETSIDI::printxy(c3.c_str(), -8, 5); //c_str sirve para convertir una string a una cadena normal
		ETSIDI::printxy("  -R y T- PARA MODIFICAR", -3, 5);
		

		string c4 = "Nivel: ";
		string c5 = to_string(mundo.get_nivel());
		string c6 = c4 + c5;
		if(mundo.get_n_enemigos()!=0)
			ETSIDI::printxy(c6.c_str(), -8, 4);
		ETSIDI::printxy("  -N y M- PARA MODIFICAR", -3, 4);

		nombre_juego.setCenter(8, -12);
		glPushMatrix();
		nombre_juego.draw();
		glPopMatrix();
	}

	else if (estado == INSTRUCCIONES) {
		gluLookAt(0.0, 7.5, 30.0,
			0.0, 7.5, 0.0,
			0.0, 1.0, 0.0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Fondo_inicio.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(1, 1); glVertex3f(-15, -4, -0.1);
		glTexCoord2d(1, 0); glVertex3f(-15, 20, -0.1);
		glTexCoord2d(0, 0); glVertex3f(15, 20, -0.1);
		glTexCoord2d(0, 1); glVertex3f(15, -4, -0.1);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
		ETSIDI::printxy("Instrucciones de juego:", -10, 15);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::printxy("Usa las teclas WASD o las flechas para controlar el coche", -10, 13);
		ETSIDI::printxy("Presiona k para cambiar de vista", -10, 12);
		ETSIDI::printxy("Presiona espacio mientras impactas con un coche para", -10, 11);
		ETSIDI::printxy("trasladarte hasta el", -10, 10);
		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::printxy("Desarrollado por:", -10, 6);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::printxy("Guillermo Barinaga Blánquez", -10, 4);
		ETSIDI::printxy("Pulsa V para volver al menu principal", -10, -2);
	}

	else if (estado == PERSONALIZAR)
	{
		Coche::setControl(0);
		float x = 6, y = 23, zm = -8, zM = 10, a = 15;
		gluLookAt  (-11.0, 0.0, 6.0,  
					4.0, 0.0, 1.0,  
					0.0, 0.0, 1.0); 

		mundo.GetCoche().rotar(0, 0, 1); //rotación del coche

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/taller.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(1, 1); glVertex3f(x, y, zm);
		glTexCoord2d(1, 0); glVertex3f(x + a, y, zM);
		glTexCoord2d(0, 0); glVertex3f(x + a, -y, zM);
		glTexCoord2d(0, 1); glVertex3f(x, -y, zm);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
		ETSIDI::printxy("PULSE LA TECLA:  -C- PARA CAMBIAR EL COLOR", 40, 15);
		ETSIDI::printxy("                 -S- PARA EMPEZAR A JUGAR", 30, 10);
		ETSIDI::printxy("                   -M- PARA VOLVER AL MENU", 23, 9);
		ETSIDI::printxy("                    -R- PARA MODIFICAR EL CIRCUITO", 18, 8);
	}


	else if (estado == JUEGO)
	{
		mundo.Dibuja();
		
		bool auxw = mundo.getKeyW();
		if (!flagw && !auxw) { ETSIDI::playMusica("musica/Relenti.mp3", true);  flagw = true; }
		if (flagw && auxw)   { ETSIDI::playMusica("musica/Acelerar.mp3", true); flagw = false; }

		bool auxd = mundo.derrape_ext();
		if (!flagd && !auxd) flagd = true; 
		if (flagd && auxd) { ETSIDI::play("musica/Derrape.wav"); flagd = false; }
	}

	else if (estado == COMIENZO)
	{
		ETSIDI::setFont("fuentes/Bitwise.ttf", 24);
		mundo.Dibuja();
		cuenta_atras++;
		if (cuenta_atras == 0 || cuenta_atras == 40 || cuenta_atras == 80 || cuenta_atras == 120)ETSIDI::play("musica/bip.wav");
		if (cuenta_atras < 40)ETSIDI::printxy("3", 100.0f, 200.0f);
		if (cuenta_atras >= 40 && cuenta_atras < 80)ETSIDI::printxy("2", 100.0f, 200.0f);
		if (cuenta_atras >= 80 && cuenta_atras < 120)ETSIDI::printxy("1", 100.0f, 200.0f);
		if (cuenta_atras >= 120) {
			cuenta_atras = 0;
			estado = JUEGO;
			ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
		}
		//No es la mejor manera de hacer la cuenta atrás debido a que esta función se llama en on draw, la cual a su vez se ejecuta asíncronamente
		//La opción correcta sería utilizar un cronómetro pero lo hemos considerado innecesario por la poca relevancia que tiene en el juego
	}
	
	else if (estado == FIN)
	{
	    ETSIDI::stopMusica();
		mundo.Dibuja();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 800, 0, 600);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
		int position = mundo.Get_Race_Position();
		string c1 = "PUESTO: ";
		string c2 = to_string(position);
		c1 = c1 + c2;

		if(mundo.get_n_enemigos())
		ETSIDI::printxy(c1.c_str(), 350, 500);

		if (mundo.Get_Race_Position() == 1 && mundo.get_n_enemigos() != 0) {
			ETSIDI::printxy("ENHORABUENA, HAS GANADO", 300, 400);
			ETSIDI::printxy(" Quien tiene magia no necesita trucos", 270, 350);
		}
		else if (mundo.Get_Race_Position() == 2)
			ETSIDI::printxy("No te fijes en lo que has perdido, si no en lo que te queda por ganar", 100, 400);

		else if (mundo.Get_Race_Position() == 3)
			ETSIDI::printxy("No importa lo lejos que llegues, si en el camino has dado lo mejor de ti mismo", 40,400);

		else if (mundo.Get_Race_Position() == 4)
			ETSIDI::printxy("Todas las batallas en la vida sirven para enseñarnos algo, incluso las que perdemos", 20, 400);

		else if (mundo.Get_Race_Position() == 5)
			ETSIDI::printxy("El fracaso es no levantarse despues de caer", 200, 400);

		else if (mundo.Get_Race_Position() == 6)
			ETSIDI::printxy("Necesitas aceptar tus derrotas para poder aprender de ellas", 125, 400);

		else if (mundo.Get_Race_Position() == 7)
			ETSIDI::printxy("El fracaso es parte de la vida, si no fracasas no aprendes", 125, 400);

		else if (mundo.Get_Race_Position() == 8)
			ETSIDI::printxy("Sabemos que es duro fracasar en algo, pero es peor NO INTENTARLO", 90, 400);

		ETSIDI::printxy("-V- VOLVER A JUGAR", 300, 300);
		ETSIDI::printxy("-M- MENU DE INICIO", 300, 250);
		ETSIDI::printxy("-S- SALIR DEL JUEGO", 300, 200);

		if (mundo.get_n_enemigos() == 0)
			ETSIDI::printxy("-F- PARA ACTIVAR EL MODO CORREDOR FANTASMA", 150, 150);

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

	else if (estado == FIN_FANTASMA)
	{
	    ETSIDI::stopMusica();
		mundo.Dibuja();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 800, 0, 600);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
		ETSIDI::printxy("-M- MENU DE INICIO", 300, 200);
		ETSIDI::printxy("-S- SALIR DEL JUEGO", 300, 150);

		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	
	else if (estado == CIRCUITO) 
	{
		gluLookAt(250, 250, 700, // posicion del ojo
			250, 251, 0,  // hacia que punto mira
			0.0, 0.0, 1.0); // definimos hacia arriba el eje Y
		mundo.dibuja_circuito(0, -2.0f);

		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
		ETSIDI::printxy("Teclas 1/3: Circuitos predefinidos", 0, 470);
		ETSIDI::printxy("Tecla 4 o A: Circuito aleatorio", 0, 450);
		ETSIDI::printxy("Tecla M: Volver al menu", 0, 50);
		ETSIDI::printxy("Tecla J: Jugar", 0, 30);
		ETSIDI::printxy("Tecla P: Personalizar", 0, 10);
	}

	else if (estado == PAUSA) 
	{
		ETSIDI::stopMusica();
		gluLookAt(250, 250, 700, // posicion del ojo
			250, 251, 0,  // hacia que punto mira
			0.0, 0.0, 1.0); // definimos hacia arriba el eje Y
		mundo.dibuja_circuito(0, -2.0f);
		ETSIDI::printxy("Pulsa P para continuar el juego", 0, 470);
		ETSIDI::printxy("Pulsa M para volver al menu", 0, 450);
		ETSIDI::printxy("Pulsa S para salir", 0, 10);
		ETSIDI::printxy("PAUSA", 230, 250);
	}
}

void Coordinador::tecla_down(unsigned char key)
{
	if (estado == INICIO)
	{
		switch (key)
		{
		case 'E':
		case 'e':
			mundo.Inicializa();
			estado = COMIENZO;
			ETSIDI::stopMusica();
			break;
		case 'r':
		case 'R':
			mundo.enemigos(0);
			break;
		case 't':
		case 'T':
			mundo.enemigos(1);
			break;
		case 'n':
		case 'N':
			mundo.set_nivel(0);
			break;
		case 'm':
		case 'M':
			mundo.set_nivel(1);
			break;
		case 'P':
		case 'p':
			ETSIDI::stopMusica();
			ETSIDI::playMusica("musica/Highway_to_Hell.mp3", true);
			estado = PERSONALIZAR;
			mundo.vistagaraje();
			break;
		case 'C':
		case 'c':
			ETSIDI::stopMusica();
			ETSIDI::playMusica("musica/Thunderstruck.mp3", true);
			estado = CIRCUITO;
			mundo.genera_circuito(0);
			mundo.dibuja_circuito(-2.0f);
			break;
		case 'i':
		case 'I':
			estado = INSTRUCCIONES;
			break;
		case 's':
		case 'S':
			exit(0);
			break;
		}
	}

	else if (estado == INSTRUCCIONES) {
		switch (key)
		{
		case 'v':
		case 'V':
			estado = INICIO;
			break;
		}
	}

	else if (estado == PERSONALIZAR)
	{
		switch (key)
		{
		case 'C':
		case 'c':
			mundo.GetCoche().setColor();
			break;
		case 'M':
		case 'm':
			estado = INICIO;
			ETSIDI::stopMusica();
			ETSIDI::playMusica("musica/Back_in_Black.mp3", true);
			break;
		case 'S':
		case 's':
			mundo.Inicializa();
			ETSIDI::stopMusica();
			estado = COMIENZO;
			break;
		case 'R':
		case 'r':
			ETSIDI::stopMusica();
			ETSIDI::playMusica("musica/Thunderstruck.mp3", true);
			estado = CIRCUITO;
			mundo.genera_circuito(0);
			mundo.dibuja_circuito(-2.0f);
			break;
			break;
		}
	}

	else if (estado == JUEGO)
	{
		mundo.TeclaDown_mundo(key);
		switch (key)
		{
		case 'P':
		case 'p':
			estado = PAUSA;
			break;
		}
	}

	else if (estado == PAUSA) {
		switch (key)
		{
		case 'p':
		case 'P':
			estado = JUEGO;
			break;
		case 'm':
		case 'M':
			estado = INICIO;
			ETSIDI::stopMusica();
			ETSIDI::playMusica("musica/Back_in_Black.mp3", true);
			break;
		case 's':
		case 'S':
			exit(0);
			break;
		}
	}
	else if (estado == FIN)
	{
		switch (key)
		{

		case 'f':
		case 'F':
			//para habilitar corredor fantasma se necesita un numero 0 de oponentes
			if (mundo.get_n_enemigos() == 0)
			{
				mundo.Fantasma() = true; //es importante ponerlo en este orden, si no se activaría la función eliminar datos
				mundo.Inicializa();
				estado = COMIENZO;
			}
			break;


		case 'm':
		case 'M':
			estado = INICIO;
			ETSIDI::stopMusica();
			ETSIDI::playMusica("musica/Back_in_Black.mp3", true);
			break;

		case 'v':
		case 'V':
			ETSIDI::stopMusica();
			mundo.Inicializa();
			estado = COMIENZO;
			break;

		case 's':
		case 'S':
			exit(0);
			break;
		}
	}

	else if (estado == FIN_FANTASMA)
	{
		switch (key)
		{
		case 'm':
		case 'M':
			mundo.Fantasma() = false;
			estado = INICIO;
			ETSIDI::playMusica("musica/Back_in_Black.mp3", true);
			break;
		case 's':
		case 'S':
			exit(0);
			break;
		}
	}


	else if (estado == CIRCUITO)
	{
		switch (key)
		{
		case '1':
			mundo.genera_circuito(0);
			break;
		case '2':
			mundo.genera_circuito(1);
			break;
		case '3':
			mundo.genera_circuito(2);
			break;
		case '4':
		case 'a':
		case 'A':
			mundo.genera_circuito(3);
			break;
		case 'm':
		case 'M':
			estado = INICIO;
			ETSIDI::stopMusica();
			ETSIDI::playMusica("musica/Back_in_Black.mp3", true);
			break;
		case 'j':
		case 'J':
			mundo.Inicializa();
			ETSIDI::stopMusica();
			estado = COMIENZO;
			break;
		case 'P':
		case 'p':
			ETSIDI::stopMusica();
			ETSIDI::playMusica("musica/Highway_to_Hell.mp3", true);
			estado = PERSONALIZAR;
			mundo.vistagaraje();
			break;
		}
	}
}

void Coordinador::tecla_up(unsigned char key)
{
	mundo.TeclaUp_mundo(key);
}

void Coordinador::tecla_up_especial(unsigned char key) {
	if(estado==JUEGO)
		mundo.TeclaUp_mundo_especial(key);
}
void Coordinador::tecla_down_especial(unsigned char key) {
	if (estado == JUEGO)
		mundo.TeclaDown_mundo_especial(key);
}

void Coordinador::mueve()
{
	if (estado == JUEGO) {
		mundo.Mueve();
		if (mundo.GetCoche().GetNvueltas() == N_VUELTAS || 
			(!mundo.get_n_enemigos() && mundo.GetCoche().GetNvueltas() == VUELTAS_MODO_F && !mundo.Fantasma()))
		{
			estado = FIN;
		}
		else if (mundo.Fantasma() && mundo.GetCoche().GetNvueltas() == VUELTAS_MODO_F)
		{
			estado = FIN_FANTASMA;
		}
	}
	else if (estado==FIN || estado== FIN_FANTASMA ) mundo.Mueve();

}