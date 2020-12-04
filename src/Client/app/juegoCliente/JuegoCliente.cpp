#include "JuegoCliente.hpp"

/* para evitar el delay por renderizar cosas viejas y no nuevas */
#define CANTIDAD_MAXIMA_DE_RONDAS_GUARDADAS 20


JuegoCliente::JuegoCliente(int cantidadJugadores,jugador_t jugadores[MAX_JUGADORES],int idPropio){
	for(int i = 0; i<cantidadJugadores;i++){
		this->jugadores[jugadores[i].mario.idImagen] = jugadores[i];
	}
	this->cantidadJugadores = cantidadJugadores;
	this->idPropio = idPropio;
	this->tiempoFaltante = 0;
	this->numeroMundo = 0;
	this->posXCamara = 0;
	this->ganaron = false;
	this->perdieron = false;
}


bool JuegoCliente::ganaronElJuego(){
	return this->ganaron;
}

bool JuegoCliente::perdieronElJuego(){
	return this->perdieron;
}


void JuegoCliente::agregarRonda(info_ronda_t ronda){
	rondas.push(ronda);
}

int JuegoCliente::obtenerPosXCamara(){
	return posXCamara;
}

void JuegoCliente::actualizar(){
	if(rondas.empty()){
		return;
	}
	info_ronda_t ronda;

	if(rondas.size() >= CANTIDAD_MAXIMA_DE_RONDAS_GUARDADAS){
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		ronda = rondas.back();
		pthread_mutex_lock(&mutex);
		while(!rondas.empty()) rondas.pop();
		pthread_mutex_unlock(&mutex);
	}else{
		ronda = rondas.front();
		rondas.pop();
	}
	tiempoFaltante = ronda.tiempoFaltante;
	numeroMundo = ronda.mundo;
	posXCamara = ronda.posXCamara;
	ganaron = ronda.ganaron;
	perdieron = ronda.perdieron;

	bloques.clear();
	enemigos.clear();
	jugadores.clear();
	monedas.clear();

	for(int i=0;i<ronda.topeBloques;i++){
		bloques.push_front(ronda.bloques[i]);
	}
	for(int i=0;i<ronda.topeEnemigos;i++){
		enemigos.push_front(ronda.enemigos[i]);
	}
	for(int i=0;i<ronda.topeMonedas;i++){
		monedas.push_front(ronda.monedas[i]);
	}
	for(int i=0;i<cantidadJugadores;i++){
		jugadores[i]=ronda.jugadores[i];
	}
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
