#include "JuegoCliente.hpp"

#define CANTIDAD_MAXIMA_DE_RONDAS_GUARDADAS 20 /* para evitar el delay por renderizar cosas viejas y no nuevas */

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

bool JuegoCliente::ganaronElJuego() const{
	return this->ganaron;
}

bool JuegoCliente::perdieronElJuego() const{
	return this->perdieron;
}

void JuegoCliente::agregarRonda(info_ronda_t ronda){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	rondas.push(ronda);
	pthread_mutex_unlock(&mutex);
}

int JuegoCliente::obtenerPosXCamara() const{
	return posXCamara;
}

void JuegoCliente::actualizar(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	if(rondas.empty()){
		return;
	}
	info_ronda_t ronda;

	if(rondas.size() >= CANTIDAD_MAXIMA_DE_RONDAS_GUARDADAS){
		ronda = rondas.back();
		pthread_mutex_lock(&mutex);
		while(!rondas.empty()) rondas.pop();
		pthread_mutex_unlock(&mutex);
	}else{
		pthread_mutex_lock(&mutex);
		ronda = rondas.front();
		rondas.pop();
		pthread_mutex_unlock(&mutex);
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
	tuberias.clear();

	for(int i=0;i<ronda.topeBloques;i++){
		bloques.push_front(ronda.bloques[i]);
	}
	for(int i=0;i<ronda.topeEnemigos;i++){
		enemigos.push_front(ronda.enemigos[i]);
	}
	for(int i=0;i<ronda.topeMonedas;i++){
		monedas.push_front(ronda.monedas[i]);
	}
    for(int i=0;i<ronda.topeTuberias;i++){
        tuberias.push_front(ronda.tuberias[i]);
    }
	for(int i=0;i<cantidadJugadores;i++){
		jugadores[i]=ronda.jugadores[i];
	}
}

int JuegoCliente::obtenerIDPropio() const{
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

int JuegoCliente::obtenerTiempoFaltante() const{
	return tiempoFaltante;
}

int JuegoCliente::obtenerMundoActual() const{
	return numeroMundo;
}

list<tuberia_t> JuegoCliente::obtenerTuberias() {
    return tuberias;
}

void JuegoCliente::agregarNivel(nivel_t nivel) {
// TODO quedarse con lo que venga
}
