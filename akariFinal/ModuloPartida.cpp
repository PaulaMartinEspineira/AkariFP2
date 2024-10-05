//Silvia Rodrigo Cañete sirodr04@ucm.es
//Paula Martin Espiñeira paumar37@ucm.es

#include"ModuloPartida.h"
#include"ModuloTablero.h"
#include"ModuloListaPosiciones.h"
#include"ModuloListaPartidas.h"
#include"ModuloCasilla.h"
#include"ModuloJuego.h"
#include"ModuloPosicion.h"
#include<iostream>
#include<fstream>

using namespace std;

ifstream& operator>>(ifstream& archivo, tPartida*& partida) {
	iniciaPartida(*partida);
	string level;
	archivo >> level >> partida->nivel;
	archivo >> partida->tablero;
	archivo >> partida->listaBombillas;
	return archivo;
}
ofstream& operator<<(ofstream& archivo, const tPartida& partida) {
	archivo << "LEVEL " << partida.nivel << "\n";
	archivo << partida.tablero;
	archivo << partida.listaBombillas;
	return archivo;
}

void iniciaPartida(tPartida& partida) {
	partida.nivel = 0;
	iniciaListaPosiciones(partida.listaBombillas);
}

//Enviamos un puntero en vez de un tPartida
void destruyePartida(tPartida*& partida){
	partida->nivel = 0;
	destruyeListaPosiciones(partida->listaBombillas);
	delete partida;
}
bool operator<(const tPartida& partida, int nivel) {
	return partida.nivel < nivel;
}
bool operator<(const tPartida& partida1, const tPartida& partida2) {
	return partida1.nivel < partida2.nivel;
}
bool juega(tPartida*& partida, int& nIt) {
	for (int i = 0; i < partida->listaBombillas.cont; i++) {
		tCasilla aux;
		aux.tipo = BOMBILLA;
		cambiaCasilla(partida->tablero, partida->listaBombillas.arrayPos[i], aux);
		cambiarIluminacion(partida->tablero, partida->listaBombillas.arrayPos[i], true);
	}

	tPos pos;
	nIt = 1;
	cout << partida->tablero;
	pedirPos(pos);
	
	while (!hasGanado(partida->tablero) && !esPosQuit(pos)) {
		//comprobamos que no queremos resetear el tablero
		if (esPosReset(pos)) {
			resetearJuego(partida->tablero);
			cout << " en el movimiento " << nIt << ".\n\n";
			cout << partida->tablero << "\n";
			pedirPos(pos);
			nIt++;
		}
		//comprobamos que la posicion existe en el tablero
		else if (PosCorrecta(pos, partida->tablero.nFils, partida->tablero.nCols)) {
			insertar(partida->listaBombillas, pos);
			ejecutarPos(partida->tablero, pos);
			cout << " en el movimiento " << nIt << ".\n\n";
			cout << partida->tablero << "\n";
			if (!hasGanado(partida->tablero)) {
				pedirPos(pos);
				nIt++;
			}
		}
		//en caso de que no exista pedimos una posicion nueva
		else {
			cout << "Introduzca una posicion correcta.\n";
			pedirPos(pos);
		}
	}
	//comprobamos si se ha ganado
	if (hasGanado(partida->tablero)) {
		cout << "Has ganado en "<<nIt<<" movimientos. :-)\n\n";
		return false;
	}
	//si no se ha ganado, se ha tenido que abandonar el juego (en el movimiento x)
	else {
		cout << " en el movimiento " << nIt << " Adeus! Adeus!" << "\n\n";
		cout << partida->tablero << "\n";
		return true;
	}
}