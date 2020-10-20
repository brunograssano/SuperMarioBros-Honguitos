

#include "Juego.h"

Juego* Juego::instanciaJuego = nullptr;

Juego* Juego::getInstance(){
	/*if(instanciaJuego==nullptr){
		instanciaJuego = new Juego("");
	}*/
	return instanciaJuego;
}

Juego* Juego::getInstance(list<Nivel*> niveles){
	if(instanciaJuego==nullptr){
		instanciaJuego = new Juego(niveles);
	}
	return instanciaJuego;
}

Mario* Juego::obtenerMario(){
	return jugador;
}

list<Enemigo*> Juego::obtenerEnemigos(){
	return niveles.front()->obtenerEnemigos();
}

list<Plataforma*> Juego::obtenerPlataformas(){
	return niveles.front()->obtenerPlataformas();
}

void Juego::actualizarPosicionesEnemigos(){
	Nivel* nivelActual = niveles.front();
	nivelActual->actualizarPosicionesEnemigos();
}

string Juego::obtenerDireccionFondoNivelActual(){
	Nivel* nivelActual = niveles.front();
	return nivelActual->obtenerDireccionFondoActual();
}

Juego::~Juego(){


	delete jugador;
	niveles.clear();
}
