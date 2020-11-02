

#include "Juego.hpp"

Juego* Juego::instanciaJuego = nullptr;

void Juego::inicializar(){
	jugador = new Mario();
}

Juego* Juego::getInstance(){
	return instanciaJuego;
}

Juego* Juego::getInstance(list<Nivel*> niveles){
	if(instanciaJuego==nullptr){
		instanciaJuego = new Juego(niveles);
	}
	return instanciaJuego;
}


void Juego::avanzarNivel(){
	Nivel* nivelViejo = niveles.front();
	delete nivelViejo;
	niveles.pop_front();
	jugador->reiniciarPosicion();

}

bool Juego::quedaSoloUnNivel(){
	return niveles.size()==1;
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

list<Moneda*> Juego::obtenerMonedas(){
	return niveles.front()->obtenerMonedas();
}

void Juego::actualizarPosicionesEnemigos(){
	Nivel* nivelActual = niveles.front();
	nivelActual->actualizarPosicionesEnemigos();
}

void Juego::sumarPuntosAJugadores(int puntos){
	jugador->agregarPuntos(puntos);
}

string Juego::obtenerDireccionFondoNivelActual(){
	Nivel* nivelActual = niveles.front();
	return nivelActual->obtenerDireccionFondoActual();
}

int Juego::obtenerTiempoDelNivel(){
	Nivel* nivelActual = niveles.front();
	return nivelActual->obtenerTiempo();
}

int Juego::obtenerPuntuacionJugador(){
	return jugador->obtenerPuntos();
}

int Juego::obtenerMundoActual(){
	Nivel* nivelActual = niveles.front();
	return nivelActual->obtenerMundo();
}

int Juego::obtenerPuntoBanderaFinActual(){
	Nivel* nivelActual = niveles.front();
	return nivelActual->obtenerPuntoBanderaFin();
}

Juego::~Juego(){


	delete jugador;
	niveles.clear();
}
