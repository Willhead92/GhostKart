#include "Camara.h"
#define PI 3.141592

Camara::Camara()
{
	pos_z = 8.0f;
	objetivo_z = 0.0f;
	distancia = 20;
}


Camara::~Camara()
{

}

void Camara::tercera_persona(Coche &j)
{
	pos_x = j.getPosx() - cos(j.getAng()*PI / 180)*distancia;
	pos_y = j.getPosy() - sin(j.getAng()*PI / 180)*distancia;
	pos_z = 8.0;
	objetivo_x = j.getPosx();
	objetivo_y = j.getPosy();

	gluLookAt(pos_x, pos_y, pos_z,                                    //posicion del ojo
		objetivo_x, objetivo_y, objetivo_z,				  //hacia que punto mira
		0, 0, 1);		  // definimos hacia arriba el eje z
}

void Camara::primera_persona(Coche &j)
{
	pos_x = j.getPosx();
	pos_y = j.getPosy();
	pos_z = 2.0f;
	objetivo_x = j.getPosx() + cos(j.getAng()*PI / 180)* distancia;
	objetivo_y = j.getPosy() + sin(j.getAng()*PI / 180)* distancia;
	objetivo_z = 0.0f;

	gluLookAt(pos_x, pos_y, pos_z,                                    //posicion del ojo
		objetivo_x, objetivo_y, objetivo_z,				  //hacia que punto mira
		0, 0, 1);
}

void Camara::vista_aerea(Coche &j)
{
	pos_x = j.getPosx() - cos(j.getAng()*PI / 180) * 15;
	pos_y = j.getPosy() - sin(j.getAng()*PI / 180) * 15;
	pos_z = 75.0;
	objetivo_x = j.getPosx() + cos(j.getAng()*PI / 180) * 15;
	objetivo_y = j.getPosy() + sin(j.getAng()*PI / 180) * 15;

	gluLookAt(pos_x, pos_y, pos_z,                                    //posicion del ojo
		objetivo_x, objetivo_y, objetivo_z,				  //hacia que punto mira
		0, 0, 1);		  // definimos hacia arriba el eje z
}
void Camara::gestion_camara(ListaCoches &l, int vista)
{
	
	if (vista == 0)
		tercera_persona(*l[Coche::getControl()]);
	if (vista == 1)
		primera_persona(*l[Coche::getControl()]);
	if (vista == 2)
		vista_aerea(*l[Coche::getControl()]);
}

