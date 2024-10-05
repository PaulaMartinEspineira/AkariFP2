//Silvia Rodrigo Cañete sirodr04@ucm.es
//Paula Martin Espiñeira paumar37@ucm.es

#include"ModuloListaPosiciones.h"
#include"ModuloPosicion.h"
#include<iostream>
#include<fstream>

using namespace std;

ifstream& operator>>(ifstream& archivo, tListaPosiciones& lp) {
	int numpos;
	tPos aux;
	archivo >> numpos;
	for (int i = 0; i < numpos; i++) {
		archivo >> aux.i >> aux.j;
		insertar(lp, aux);
	}
	return archivo;
}
ofstream& operator<<(ofstream& archivo, const tListaPosiciones& lp) {
	archivo << lp.cont << "\n";
	for (int i = 0; i < lp.cont; i++) {
		archivo << lp.arrayPos[i].i << " " << lp.arrayPos[i].j << "\n";
	}
	return archivo;
}

void iniciaListaPosiciones(tListaPosiciones& lp) {
	lp.cont = 0;
	lp.size = DIM;
	lp.arrayPos = new tPos[lp.size];
}
void destruyeListaPosiciones(tListaPosiciones& lp) {
	delete lp.arrayPos;
	lp.arrayPos = nullptr;
	lp.size = 0;
	lp.cont = 0;
}
void insertar(tListaPosiciones& lp, const tPos& pos) {
	if (lp.cont < lp.size) {
		lp.arrayPos[lp.cont] = pos;
		lp.cont++;
	}
	else {
		tPos* aux = nullptr;
		int tamano = 2 * lp.size;
		aux = new tPos[tamano];
		for (int i = 0; i < lp.size; i++) {
			aux[i] = lp.arrayPos[i];
		}
		delete[] lp.arrayPos;
		lp.arrayPos = aux;
		lp.size *= lp.size;
		aux = nullptr;
		lp.arrayPos[lp.cont] = pos;
		lp.cont++;
	}
}
int dameNumElem(const tListaPosiciones& lp) {
	return lp.cont;
}
tPos dameElem(const tListaPosiciones& lp, int i) {
	return lp.arrayPos[i];
}