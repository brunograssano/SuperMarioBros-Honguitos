

#include "Nivel.h"



void Nivel::actualizarPosicionesEnemigos(){
	for (auto const& enemigo : enemigos) {
	    enemigo->actualizarPosicion();
	}
}

list<Enemigo*> Nivel::obtenerEnemigos(){
	return enemigos;
}

string Nivel::obtenerDireccionFondoActual(){
	return direccionFondo;
}

void Nivel::inicializarPosicionEnemigo(){
	int coordenadaX = 20;
	for (auto const& enemigo : enemigos) {
	    enemigo->agregarPosicion(coordenadaX,50);
	    coordenadaX += 200;
	}
}
