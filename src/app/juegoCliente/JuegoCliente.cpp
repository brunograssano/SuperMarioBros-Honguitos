

#include "JuegoCliente.hpp"


JuegoCliente::JuegoCliente(int cantidadJugadores,jugador_t jugadores[MAX_JUGADORES],int idPropio){
	for(int i = 0; i<cantidadJugadores;i++){
		this->jugadores[jugadores[i].mario.idImagen] = jugadores[i];
	}
	this->cantidadJugadores = cantidadJugadores;
	this->idPropio = idPropio;
	this->tiempoFaltante = 0;
	this->tiempoDeInicio = 0;
	this->numeroMundo = 0;
}


int JuegoCliente::obtenerIDPropio(){
	return idPropio;
}

map<int,jugador_t> JuegoCliente::obtenerJugadores(){
	return jugadores;
}

list<enemigo_t> JuegoCliente::obtenerEnemigos(){
	return enemigos;
}

list<bloque_t> JuegoCliente::obtenerBloques(){
	return bloques;
}

list<moneda_t> JuegoCliente::obtenerMonedas(){
	return monedas;
}

int JuegoCliente::obtenerTiempoFaltante(){
	return tiempoFaltante;
}

int JuegoCliente::obtenerMundoActual(){
	return numeroMundo;
}
