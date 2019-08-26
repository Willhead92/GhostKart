#include "ListaCoches.h"



ListaCoches::ListaCoches()
{
	nElem = 0;
	for (int i = 0; i < MAX_COCHES; i++)
		lista[i] = NULL;
}


ListaCoches::~ListaCoches()
{

}

bool ListaCoches::agregar(Coche *c) 
{
	if (nElem >= MAX_COCHES) return false;
		
	lista[nElem++] = c;
	return true;
}

void ListaCoches::dibuja() {
	for (int i = 0; i < nElem; i++)
		lista[i]->dibuja();
}

void ListaCoches::mover(int ac, int gir, float t)
{
	int c = Coche::getControl();

	for (int i = 0; i < nElem; i++) {

		if (i != c) {
			lista[i]->mover(t);
		}
		else if (i == c && lista[c]->GetNvueltas() == N_VUELTAS ||
			(nElem == 1 && lista[0]->GetNvueltas() == VUELTAS_MODO_F))  //el orden de los else if establece prioridad
		{
			lista[i]->mover(t);
		}
		else if (i == c && lista[c]->GetNvueltas()< N_VUELTAS ){
			lista[i]->mover(ac, gir, t);
		}
	
	}
}

void ListaCoches::eliminar(int index) {
	if ((index < 1) || (index >= nElem))
		return;
	delete lista[index]; lista[index] = NULL;
	nElem--;
	for (int i = index; i < nElem; i++)
		lista[i] = lista[i + 1];
}

void ListaCoches::eliminarLista() {
	for (int i = 1; i < nElem; i++)
	{
		delete lista[i];
		lista[i] = NULL;
	}
	nElem = 1;
}

Coche* ListaCoches::operator [](int i) {
	if (i >= nElem)//si me paso, devuelvo la ultima
		i = nElem - 1;
	if (i < 0) //si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
}

void ListaCoches::setInfo(GestorCircuitos circ) {
	for (int i = 0; i < nElem; i++){
		lista[i]->setInfo(circ.GetInfo(lista[i]->getPosx(), lista[i]->getPosy(), lista[i]->getN_sig()));
	}
}

void ListaCoches::vistaGaraje() {
	lista[0]->SetPos(0.0f,0.0f,0.0f);
}

void ListaCoches::parrillaSalida() {
	lista[0]->SetPos(100.0f, 200.0f, 90.0f);
	for (int i = 1; i < nElem; i=i+2) {
		lista[i]->SetPos(95.0f,i*10.0f+200.0f,90.0f);
	}
	for (int i = 2; i < nElem; i = i + 2) {
		lista[i]->SetPos(105.0f, i*10.0f + 200.0f, 90.0f);
	}
	for (int i = 0; i < nElem; i++) {
		lista[i]->Parar();
	}
}

void ListaCoches::SetV_MAX(int V) {
	for (int i = 0; i < nElem; i++) {
		lista[i]->setV_MAX(V);
	}
}

void ListaCoches::rebote(bool aux) { 
	if(nElem>1){
		for (int i = 0; i < nElem; i++) {
			for (int j = i+1; j < nElem; j++) {
				if (Interaccion::colision(*(lista[i]), *(lista[j])) == 1 &&(i==Coche::getControl()||j==Coche::getControl())) {
					if (aux == 1) {
						if (i == Coche::getControl() && lista[i]->getVelAbs() < lista[j]->getVelAbs())Coche::setControl(j);
						else if (j == Coche::getControl() && lista[j]->getVelAbs() < lista[i]->getVelAbs())Coche::setControl(i);
						ETSIDI::play("musica/blip.wav");
					}
					else ETSIDI::play("musica/hit.wav");
				}
			}
		}
	}
}

void ListaCoches::limites() {
	Interaccion::colision(*lista[Coche::getControl()]);
}

void ListaCoches::Calcula_Posicion() {
	
	race_position = nElem;

	for (int i = 0; i < nElem; i++)
	{
		if (i != Coche::getControl())
		{
			if (lista[i]->GetNacumulado() < lista[Coche::getControl()]->GetNacumulado())
				race_position--;
		}
	}
}

int ListaCoches::GetVueltas() {
	return lista[Coche::getControl()]->GetNvueltas();
}