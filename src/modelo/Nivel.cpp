
#include <string>
#include "Nivel.h"
#include "../log/Log.h"


void Nivel::actualizarPosicionesEnemigos(){
	Log* log = Log::getInstance();
	int i = 1;
	for (auto const& enemigo : enemigos) {
	    enemigo->actualizarPosicion();
	    log->mostrarPosicion("Enemigo " + to_string(i), enemigo->obtenerPosicionX(), enemigo->obtenerPosicionY());
	    i++;
	}
}

list<Enemigo*> Nivel::obtenerEnemigos(){
	return enemigos;
}
list<Plataforma*> Nivel::obtenerPlataformas(){
	return plataformas;
}

list<Moneda*> Nivel::obtenerMonedas(){
	return monedas;
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
