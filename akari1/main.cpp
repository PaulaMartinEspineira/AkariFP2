//Silvia Rodrigo Cañete sirodr04@ucm.es
//Paula Martin Espiñeira paumar37@ucm.es
#include"ModuloTablero.h"
#include"ModuloCasilla.h"
#include"ModuloJuego.h"
#include"ModuloPosicion.h"
#include<iostream>
#include<fstream>
#include<iomanip>


using namespace std;

int main() {
	tPos pos;
	tTablero tablero;
	cin >> tablero;
	cout << tablero << "\n";
	int cont = 1;
	pedirPos(pos);
	//jugamos hasta que se gane o se abandone la partida
	while (!hasGanado(tablero) && !esPosQuit(pos)) {
		//comprobamos que no queremos resetear el tablero
		if (esPosReset(pos)) {
			resetearJuego(tablero);
			system("cls");
			cout << tablero << "\n";
			pedirPos(pos);
			cont++;
		}
		//comprobamos que la posicion existe en el tablero
		else if (PosCorrecta(pos, tablero.nFils, tablero.nCols)) {
			ejecutarPos(tablero, pos);
			system("cls");
			cout << tablero << "\n";
			if (!hasGanado(tablero)) {
				pedirPos(pos);
				cont++;
			}
		}
		//en caso de que no exista pedimos una posicion nueva
		else {
			pedirPos(pos);
		}
	}
	return 0;
}