

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


Juego::~Juego(){
	// Se borran los niveles/vamos borrando a medida que se avanza?
	delete jugador;
}
