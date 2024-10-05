//Silvia Rodrigo Cañete sirodr04@ucm.es
//Paula Martin Espiñeira paumar37@ucm.es

#include"ModuloListaPartidas.h"
#include"ModuloPartida.h"
#include<iostream>

using namespace std;

ifstream& operator>>(ifstream& archivo, tListaPartidas& listaPartidas) {
	int numPartidas;
	archivo >> numPartidas;
	for (int i = 0; i < numPartidas; i++) {
		listaPartidas.datos[i] = new tPartida;
		archivo >> listaPartidas.datos[i];
		listaPartidas.nElem++;
		insertarOrd(listaPartidas, *listaPartidas.datos[i]);
	}
	return archivo;
}

ofstream& operator<<(ofstream& archivo, const tListaPartidas& listaPartidas) {
	archivo << listaPartidas.nElem << "\n";
	for (int i = 0; i < listaPartidas.nElem; i++) {
		archivo << *listaPartidas.datos[i];
	}
	return archivo;
}



//Preguntar si queda mejor con intercambiar (tendríamos que borrar todos los q hemos creado?)
void intercambiar(tPartida*& x, tPartida*& y) {
	tPartida* aux = x;
	x = y;
	y = aux;
}

void insertarOrd(tListaPartidas& listaPartidas, const tPartida& partida) {
	if (listaPartidas.nElem == 1);
	else {
		int pos2 = 0;
		while (listaPartidas.datos[pos2]->nivel > listaPartidas.datos[listaPartidas.nElem - 1]->nivel && pos2 < listaPartidas.nElem) {
			intercambiar(listaPartidas.datos[pos2], listaPartidas.datos[listaPartidas.nElem - 1]);
			pos2++;
		}
	}
}
void destruyeListaPartidas(tListaPartidas& listaPartidas) {
	for (int i = 0; i < listaPartidas.nElem; i++) {
		destruyePartida(listaPartidas.datos[i]);
		listaPartidas.datos[i] = nullptr;
	}
	//listaPartidas.datos = nullptr;
	listaPartidas.nElem = 0;
}

int buscaPos(const tListaPartidas& listaPartidas, int nivel) {
	bool encontrado = false;
	int mitad, ini = 0, fin = listaPartidas.nElem;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (listaPartidas.datos[mitad]->nivel == nivel) {
			encontrado = true;
		}
		else if (nivel < listaPartidas.datos[mitad]->nivel) {
			fin = mitad - 1;
		}
		else {
			ini = mitad + 1;
		}
	}
	if (encontrado) {
		return mitad;
	}
	else return -1;
}

tPartida* dameElem(const tListaPartidas& listaPartidas, int pos) {
	if (pos < listaPartidas.nElem) {
		return listaPartidas.datos[pos];
	}
	else return NULL;
}

int dameNumElem(const tListaPartidas& listaPartidas) {
	return listaPartidas.nElem;
}

void eliminarPartida(tListaPartidas& listaPartidas, const tPartida& partida) {
	int pos = buscaPos(listaPartidas, partida.nivel);
	destruyePartida(listaPartidas.datos[pos]);
	listaPartidas.datos[pos] = nullptr;
	for (int i = pos; i < listaPartidas.nElem - 1; i++) {
		listaPartidas.datos[i] = listaPartidas.datos[i + 1];
	}
	pos = listaPartidas.nElem - 1;
	listaPartidas.datos[pos] = nullptr;
	listaPartidas.nElem--;
}
