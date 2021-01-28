#include "JuegoCliente.hpp"
#include "src/Utils/Constantes.hpp"

#define CANTIDAD_MAXIMA_DE_RONDAS_GUARDADAS 20 /* para evitar el delay por renderizar cosas viejas y no nuevas */
#define RANGO_VISTA 100
#define NO_HAY_MUNDO_CARGADO (-1)

pthread_mutex_t mutexJuegoCliente = PTHREAD_MUTEX_INITIALIZER;

bool operator == (const entidad_t &bloque1, const entidad_t &bloque2){
    return bloque1.x == bloque2.x && bloque1.y == bloque2.y && bloque1.recorteY == bloque2.recorteY;
}


JuegoCliente::JuegoCliente(int cantidadJugadores,jugador_t jugadores[],int idPropio,int anchoPantalla,int altoPantalla,
                           podio_t podios[], unsigned short topePodios, podio_t podioPuntosAcumulados){
	for(int i = 0; i<cantidadJugadores;i++){
		this->jugadores[jugadores[i].mario.idImagen] = jugadores[i];
	}
	this->cantidadJugadores = cantidadJugadores;
	this->idPropio = idPropio;
	this->tiempoFaltante = 0;
	this->numeroMundo = NO_HAY_MUNDO_CARGADO;
	this->nivelesJugados = 0;
	this->ganaron = false;
	this->perdieron = false;
	this->anchoVista = anchoPantalla;
	this->hayQueMostrarPuntosDeNivel = false;
	this->hayQueCargarPodioNivel = true;
    rectanguloCamara = { 0, 0, anchoPantalla , altoPantalla};
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
	pthread_mutex_lock(&mutexJuegoCliente);
	rondas.push(ronda);
	pthread_mutex_unlock(&mutexJuegoCliente);
}

SDL_Rect JuegoCliente::obtenerCamara()const{
	return rectanguloCamara;
}

void JuegoCliente::cargarLista(std::list<entidad_t>* listaACargar, entidad_t *vector, unsigned short tope) {
    listaACargar->clear();
    for(int i=0;i<tope;i++){
        listaACargar->push_front(vector[i]);
    }
}

void JuegoCliente::actualizar(){
	if(rondas.empty()){
		return;
	}
	info_ronda_t ronda;

	if(rondas.size() >= CANTIDAD_MAXIMA_DE_RONDAS_GUARDADAS){
		ronda = rondas.back();
		pthread_mutex_lock(&mutexJuegoCliente);
		while(!rondas.empty()) rondas.pop();
		pthread_mutex_unlock(&mutexJuegoCliente);
	}else{
		pthread_mutex_lock(&mutexJuegoCliente);
		ronda = rondas.front();
		rondas.pop();
		pthread_mutex_unlock(&mutexJuegoCliente);
	}
	tiempoFaltante = ronda.tiempoFaltante;
    rectanguloCamara.x = ronda.posXCamara;
	ganaron = ronda.ganaron;
	perdieron = ronda.perdieron;

	cargarLista(&bloques,ronda.bloques,ronda.topeBloques);
    cargarLista(&enemigos,ronda.enemigos,ronda.topeEnemigos);
    cargarLista(&monedas,ronda.monedas,ronda.topeMonedas);
    cargarLista(&efectos,ronda.efectos,ronda.topeEfectos);

	for(int i=0;i<cantidadJugadores;i++){
		jugadores[i].mario=ronda.jugadores[i];
	}

    std::list<entidad_t> ladrillosASacar;
    std::list<entidad_t> ladrillosNuevos;
    bool agregado = false;
    for(auto ladrillo: ladrillos){
        if(enRango(ladrillo.x, LARGO_BLOQUE)){
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

std::map<int,jugador_t> JuegoCliente::obtenerJugadores(){
	return jugadores;
}

std::list<entidad_t> JuegoCliente::obtenerEnemigos(){
	return enemigos;
}

std::list<entidad_t> JuegoCliente::obtenerBloques(){
	return bloques;
}

bool JuegoCliente::enRango(int posX, int w) const {
    return (rectanguloCamara.x - RANGO_VISTA) <= posX + w && posX <= (rectanguloCamara.x + anchoVista + RANGO_VISTA);
}

std::list<entidad_t> JuegoCliente::obtenerMonedas(){
	return monedas;
}

std::vector<podio_t> JuegoCliente::obtenerPodios(){
    return this->podios;
}

int JuegoCliente::obtenerTiempoFaltante() const{
	return tiempoFaltante;
}

int JuegoCliente::obtenerMundoActual() const{
	return numeroMundo;
}

std::list<entidad_t> JuegoCliente::obtenerPozos() {
    std::list<entidad_t> pozosAMostrar;
    for(auto pozo:pozos){
        if(enRango(pozo.x, ANCHO_POZO)){
            pozosAMostrar.push_front(pozo);
        }
    }
    return pozosAMostrar;
}


std::list<entidad_t> JuegoCliente::obtenerTuberias() {
    std::list<entidad_t> tuberiasAMostrar;
    for(auto tuberia:tuberias){
        int ancho = tuberia.tipo==TUBERIA_CHICA?ANCHO_TUBERIA_CHICA:ANCHO_TUBERIA_GRANDE;
        if(enRango(tuberia.x, ancho)){
            tuberiasAMostrar.push_front(tuberia);
        }
    }
    return tuberiasAMostrar;
}

std::list<entidad_t> JuegoCliente::obtenerEfectos() {
    return efectos;
}

void JuegoCliente::agregarNivel(nivel_t nivel) {
    pthread_mutex_lock(&mutexJuegoCliente);
    if(numeroMundo != NO_HAY_MUNDO_CARGADO ){
        this->hayQueMostrarPuntosDeNivel = true;
    }
    numeroMundo = nivel.mundo;

    cargarLista(&ladrillos,nivel.bloques,nivel.topeBloques);
    cargarLista(&tuberias,nivel.tuberias,nivel.topeTuberias);
    cargarLista(&pozos,nivel.pozos,nivel.topePozos);

    if(!hayQueCargarPodioNivel){
        hayQueCargarPodioNivel = true;
    }else{
        podios.push_back(nivel.podio);
    }

    podioPuntosTotales = nivel.podioPuntosAcumulados;
    nivelesJugados++;

    pthread_mutex_unlock(&mutexJuegoCliente);

}

int JuegoCliente::obtenerNivelesJugados() const  {
    return nivelesJugados;
}

podio_t JuegoCliente::obtenerPodioPuntosAcumulados() {
    return this->podioPuntosTotales;
}