//Silvia Rodrigo Cañete sirodr04@ucm.es
//Paula Martin Espiñeira paumar37@ucm.es
#include"ModuloTablero.h"
#include"ModuloCasilla.h"
#include"ModuloPosicion.h"
#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

//CARGA DE TABLERO
istream& operator>>(istream& in, tTablero& tablero) {
	fstream archivo;
	archivo.open("tablero");
	if (archivo.is_open()) {
		archivo >> tablero.nFils >> tablero.nCols;
		char casilla = ' ';
		for (int i = 0; i < tablero.nFils; i++) {
			for (int j = 0; j < tablero.nCols; j++) {
				archivo >> casilla;
				if (casilla == '.') {
					tablero.datos[i][j].tipo = LIBRE;
					tablero.datos[i][j].numBombillas = 0;
				}
				else if (casilla == 'X') {
					tablero.datos[i][j].tipo = PARED;
					tablero.datos[i][j].numBombillas = -1;
				}
				else {
					int num = casilla - 48;
					tablero.datos[i][j].tipo = PARED;
					tablero.datos[i][j].numBombillas = num;
				}

			}
		}
		return in;
	}
}

//IMPRIMIMOS TABLERO
ostream& operator<<(ostream& out, tTablero& tablero) {
	out << "	 |";
	for (int j = 0; j < tablero.nCols; j++) {
		out << " " << BLUE << j << RESET << " |";
	}
	out << "\n" << "	" << "-+";
	for (int j = 0; j < tablero.nCols; j++) {
		out << setfill('-') << setw(4) << "+";
	}
	out << "\n";
	for (int i = 0; i < tablero.nFils; i++) {
		out << "	";
		out << BLUE << i << RESET << "|";
		for (int j = 0; j < tablero.nCols; j++) {
			if (tablero.datos[i][j].tipo == LIBRE) {
				if (tablero.datos[i][j].numBombillas == 0) {
					out << BG_WHITE << "   " << RESET << "|";
				}
				else {
					out << BG_YELLOW << "   " << RESET << "|";
				}
			}
			else if (tablero.datos[i][j].tipo == PARED) {
				if (tablero.datos[i][j].numBombillas == -1) {
					out << setfill(' ') << setw(4) << "|";
				}
				else {
					out << setfill(' ') << setw(3) << tablero.datos[i][j].numBombillas << "|";
				}
			}
			else {
				out << BG_YELLOW << "  " << RED << "*" << RESET << "|";
			}
		}
		out << "\n" <<  "	"  << "-+";
		for (int j = 0; j < tablero.nCols; j++) {
			out << setfill('-') << setw(4) << "+";
		}
		out << "\n";
	}
	return out;
}

//separamos en un struct la posicion del tablero con la que queremos trabajar
tCasilla casillaEnPos(tTablero const& tablero, tPos pos) {
	return tablero.datos[pos.i][pos.j];
}
//actualizamos los datos del tablero despues de modificar una posicion
void cambiaCasilla(tTablero& tablero, tPos pos, tCasilla laCasilla) {
	tablero.datos[pos.i][pos.j] = laCasilla;
}
