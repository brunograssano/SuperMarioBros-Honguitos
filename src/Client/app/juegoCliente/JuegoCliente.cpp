#include "JuegoCliente.hpp"
#include "src/Utils/Constantes.hpp"

#define CANTIDAD_MAXIMA_DE_RONDAS_GUARDADAS 20 /* para evitar el delay por renderizar cosas viejas y no nuevas */
#define RANGO_VISTA 100
#define NO_HAY_MUNDO_CARGADO -1

bool operator == (const bloque_t &bloque1, const bloque_t &bloque2){
    return bloque1.posX == bloque2.posX && bloque1.posY == bloque2.posY && bloque1.numeroRecorteY == bloque2.numeroRecorteY;
}


JuegoCliente::JuegoCliente(int cantidadJugadores,jugador_t jugadores[],int idPropio,int anchoPantalla, podio_t podios[], unsigned short topePodios, podio_t podioPuntosAcumulados){
	for(int i = 0; i<cantidadJugadores;i++){
		this->jugadores[jugadores[i].mario.idImagen] = jugadores[i];
	}
	this->cantidadJugadores = cantidadJugadores;
	this->idPropio = idPropio;
	this->tiempoFaltante = 0;
	this->numeroMundo = NO_HAY_MUNDO_CARGADO;
	this->posXCamara = 0;
	this->nivelesJugados = 0;
	this->ganaron = false;
	this->perdieron = false;
	this->anchoVista = anchoPantalla;
	this->hayQueMostrarPuntosDeNivel = false;
	this->hayQueCargarPodioNivel = true;
	for(int i = 0; i<topePodios; i++){
	    if(i == 0){
	        podio_t primerPodio;
	        this->podios.push_back(primerPodio);
	    }
	    this->hayQueCargarPodioNivel = false;
	    this->podios.push_back(podios[i]);
	    nivelesJugados++;
	}

	this->podioPuntosTotales = podioPuntosAcumulados;
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
        if(enRango(ladrillo.posX, LARGO_BLOQUE)){
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

bool JuegoCliente::enRango(int posX, int w) const {
    return (posXCamara - RANGO_VISTA) <= posX + w && posX <= (posXCamara + anchoVista + RANGO_VISTA);
}

list<moneda_t> JuegoCliente::obtenerMonedas(){
	return monedas;
}

vector<podio_t> JuegoCliente::obtenerPodios(){
    return this->podios;
}

int JuegoCliente::obtenerTiempoFaltante() const{
	return tiempoFaltante;
}

int JuegoCliente::obtenerMundoActual() const{
	return numeroMundo;
}

list<pozo_t> JuegoCliente::obtenerPozos() {
    list<pozo_t> pozosAMostrar;
    for(auto pozo:pozos){
        if(enRango(pozo.posX, ANCHO_POZO)){
            pozosAMostrar.push_front(pozo);
        }
    }
    return pozosAMostrar;
}


list<tuberia_t> JuegoCliente::obtenerTuberias() {
    list<tuberia_t> tuberiasAMostrar;
    for(auto tuberia:tuberias){
        int ancho = tuberia.tipo==TUBERIA_CHICA?ANCHO_TUBERIA_CHICA:ANCHO_TUBERIA_GRANDE;
        if(enRango(tuberia.posX, ancho)){
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
    if(numeroMundo != NO_HAY_MUNDO_CARGADO ){
        this->hayQueMostrarPuntosDeNivel = true;
    }
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

    if(!hayQueCargarPodioNivel){
        hayQueCargarPodioNivel = true;
    }else{
        podios.push_back(nivel.podio);
    }

    podioPuntosTotales = nivel.podioPuntosAcumulados;
    nivelesJugados++;

    pthread_mutex_unlock(&mutex);

}

int JuegoCliente::obtenerNivelesJugados()  {
    return nivelesJugados;
}

podio_t JuegoCliente::obtenerPodioPuntosAcumulados() {
    return this->podioPuntosTotales;
}