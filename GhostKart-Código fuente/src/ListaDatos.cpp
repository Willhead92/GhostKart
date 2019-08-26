#include "ListaDatos.h"


ListaDatos::~ListaDatos()
{
	delete[]lista;
	lista = NULL;
}

void ListaDatos::operator+=(Coche &c)
{
	if (num == MAX)
	{
		MAX += 10000;
		datos *lista_aux = new datos[MAX];//creamos una lista auxiliar capaz de contener el nuevo numero máximo de elementos
		for (int i = 0; i < num; i++) lista_aux[i] = lista[i];
		delete[] lista;
		lista = lista_aux;
	}
	lista[num].posicion = c.getPos();
	lista[num].angulo = c.getAng();
	printf("%f,  %f,  %d\n", lista[num].posicion.x, lista[num].posicion.y, num);
	num++;
}

void ListaDatos::eliminarDatos()
{
	for (int i = 0; i < num; i++)
	{
		lista[i].posicion.x = 0;
		lista[i].posicion.y = 0;
		lista[i].angulo = 0;
	}
	num = 0;
}
