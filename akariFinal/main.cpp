//Silvia Rodrigo Cañete sirodr04@ucm.es
//Paula Martin Espiñeira paumar37@ucm.es
#include"ModuloTablero.h"
#include"ModuloCasilla.h"
#include"ModuloJuego.h"
#include"ModuloPosicion.h"
#include"ModuloPartida.h"
#include"ModuloListaPartidas.h"
#include"ModuloListaPosiciones.h"
#include<iostream>
#include<fstream>
#include<iomanip>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>


using namespace std;

int main() {
	tListaPartidas listaPartidas;
	cout << "Dame el nombre del fichero que contiene el tablero: ";
	string fich_nombre;
	cin >> fich_nombre;
	ifstream archivo;
	archivo.open(fich_nombre);
	if (!archivo.is_open()) {
		cout << "Por favor introduzca el nombre de un fichero valido.\n";
	}
	else {
		archivo >> listaPartidas;
		archivo.close();

		cout << "\nDame el nivel a jugar (>0): ";
		int nivel;
		cin >> nivel;
		int pos = buscaPos(listaPartidas, nivel);
		while (pos == -1 && nivel < listaPartidas.datos[listaPartidas.nElem-1]->nivel) {
			nivel++;
			pos = buscaPos(listaPartidas, nivel);
		}
		if (nivel > listaPartidas.datos[listaPartidas.nElem-1]->nivel) {
			nivel = listaPartidas.datos[listaPartidas.nElem-1]->nivel;
		}
		int nIt = 0;
		bool abandonado = juega(listaPartidas.datos[pos], nIt);
		if (!abandonado) {
			eliminarPartida(listaPartidas, *listaPartidas.datos[pos]);
		}

		cout << "Dame el nombre del archivo para guardar: ";
		cin >> fich_nombre;
		ofstream archivo;
		archivo.open(fich_nombre);
		archivo << listaPartidas;
		archivo.close();

		destruyeListaPartidas(listaPartidas);
	}
	_CrtDumpMemoryLeaks();
	return 0;
}