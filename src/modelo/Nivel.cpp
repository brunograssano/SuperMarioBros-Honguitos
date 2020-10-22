

#include "Nivel.h"



void Nivel::actualizarPosicionesEnemigos(){
	for (auto const& enemigo : enemigos) {
	    enemigo->actualizarPosicion();
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
