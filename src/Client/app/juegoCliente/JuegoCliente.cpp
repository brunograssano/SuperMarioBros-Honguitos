#include "JuegoCliente.hpp"

#define CANTIDAD_MAXIMA_DE_RONDAS_GUARDADAS 20 /* para evitar el delay por renderizar cosas viejas y no nuevas */
#define RANGO_VISTA 100

bool operator == (const bloque_t &bloque1, const bloque_t &bloque2){
    return bloque1.posX == bloque2.posX && bloque1.posY == bloque2.posY && bloque1.numeroRecorteY == bloque2.numeroRecorteY;
}


JuegoCliente::JuegoCliente(int cantidadJugadores,jugador_t jugadores[MAX_JUGADORES],int idPropio,int anchoPantalla){
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
	this->anchoVista = anchoPantalla;
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
	posXCamara = ronda.posXCamara;
	ganaron = ronda.ganaron;
	perdieron = ronda.perdieron;

	bloques.clear();
	enemigos.clear();
	jugadores.clear();
	monedas.clear();
	efectos.clear();

	for(int i=0;i<ronda.topeBloques;i++){ // TODO PENSAR FORMA DE SACAR LO REPETIDO // sizeof(objeto), comienzo del vector
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
    for(int i=0;i<ronda.topeEfectos;i++){
        efectos.push_front(ronda.efectos[i]);
    }

    list<bloque_t> ladrillosASacar;
    list<bloque_t> ladrillosNuevos;
    bool agregado = false;
    for(auto ladrillo: ladrillos){
        if(enRango(ladrillo.posX)){
            for(auto bloque : bloques) {
                if(ladrillo == bloque){
                    ladrillosASacar.push_front(ladrillo);
                    ladrillosNuevos.push_front(bloque);
                    agregado = true;
                }
            }
            if(!agregado){
                bloques.push_front(ladrillo);
            }
            agregado = false;
        }
    }
    for (auto ladrillo : ladrillosASacar){
        ladrillos.remove(ladrillo);
    }
    for (auto ladrillo : ladrillosNuevos){
        ladrillos.push_front(ladrillo);
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

bool JuegoCliente::enRango(int posX) const {
    return (posXCamara - RANGO_VISTA) <= posX && posX <= (posXCamara + anchoVista + RANGO_VISTA);
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
    list<tuberia_t> tuberiasAMostrar;
    for(auto tuberia:tuberias){
        if(enRango(tuberia.posX)){
            tuberiasAMostrar.push_front(tuberia);
        }
    }
    return tuberiasAMostrar;
}

list<efecto_t> JuegoCliente::obtenerEfectos() {
    return efectos;
}

void JuegoCliente::agregarNivel(nivel_t nivel) {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    numeroMundo = nivel.mundo;
    ladrillos.clear();
    tuberias.clear();
    pozos.clear();
    for(int i=0;i<nivel.topeBloques;i++){ // TODO IDEM A LO DE ARRIBA
        ladrillos.push_front(nivel.bloques[i]);
    }
    for(int i=0;i<nivel.topeTuberias;i++){
        tuberias.push_front(nivel.tuberias[i]);
    }
    for(int i=0;i<nivel.topePozos;i++){
        pozos.push_front(nivel.pozos[i]);
    }
    pthread_mutex_unlock(&mutex);
}