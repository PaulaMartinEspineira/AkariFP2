//Silvia Rodrigo Cañete sirodr04@ucm.es
//Paula Martin Espiñeira paumar37@ucm.es
#include"ModuloCasilla.h"
#include<iostream>

using namespace std;

//ilumina una casilla libre, sumando uno al numero de bombillas que la iluminan
void iluminarCasilla(tCasilla& casilla) {
	if (casilla.tipo != PARED) {
		casilla.numBombillas++;
	}
}
//desilumina una casilla libre, restando uno al numero de bombillas que la iluminan
void desiluminarCasilla(tCasilla& casilla) {
	if (casilla.tipo != PARED) {
		casilla.numBombillas--;
	}
}