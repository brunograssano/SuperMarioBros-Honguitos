

#include "Juego.h"

Juego* Juego::instanciaJuego = nullptr;

Juego* Juego::getInstance(){
	if(instanciaJuego==nullptr){ // TODO Ver si le pasamos el por defecto, o si lo sacamos directamente
		instanciaJuego = new Juego("");
	}
	return instanciaJuego;
}

Juego* Juego::getInstance(string direccionConfiguracion){
	if(instanciaJuego==nullptr){
		instanciaJuego = new Juego(direccionConfiguracion);
	}
	return instanciaJuego;
}

Mario* Juego::obtenerMario(){
	return jugador;
}

list<Enemigo*> Juego::obtenerEnemigos(){
	return niveles.front()->obtenerEnemigos();
}

void Juego::actualizarPosicionesEnemigos(){
	Nivel* nivelActual = niveles.front();
	nivelActual->actualizarPosicionesEnemigos();
}

Juego::~Juego(){
	// Se borran los niveles/vamos borrando a medida que se avanza?
	delete jugador;

	// ESTO BORRA SOLO A UNO, LLAMA A SU DESTRUCTOR
	niveles.pop();
}
