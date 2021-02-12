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

void JuegoCliente::crearListaDeFondoPozo(std::list<entidad_t>* listaACargar, entidad_t *pozos, uint8_t topePozos) {
    listaACargar->clear();
    for(int i = 0; i < topePozos; i++){
        entidad_t fondo = pozos[i];
        fondo.tipo = FONDO_POZO;
        fondo.recorteY = fondo.recorteX;
        fondo.recorteX = 0;
        listaACargar->push_front(fondo);
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

	cargarLista(&entidades[BLOQUE], ronda.bloques, ronda.topeBloques);
    cargarLista(&entidades[ENEMIGOS_RECORTE],ronda.enemigos,ronda.topeEnemigos);
    cargarLista(&entidades[MONEDA], ronda.monedas, ronda.topeMonedas);
    cargarLista(&entidades[EFECTOS_RECORTE],ronda.efectos,ronda.topeEfectos);

	for(int i=0;i<cantidadJugadores;i++){
		jugadores[i].mario=ronda.jugadores[i];
	}

    std::list<entidad_t> ladrillosASacar;
    std::list<entidad_t> ladrillosNuevos;
    bool agregado = false;
    pthread_mutex_lock(&mutexJuegoCliente);
    for(auto ladrillo: ladrillos){
        if(enRango(ladrillo.x, LARGO_BLOQUE)){
            for(auto bloque : entidades[BLOQUE]) {
                if(ladrillo == bloque){
                    ladrillosASacar.push_front(ladrillo);
                    ladrillosNuevos.push_front(bloque);
                    agregado = true;
                }
            }
            if(!agregado){
                entidades[BLOQUE].push_front(ladrillo);
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
    pthread_mutex_unlock(&mutexJuegoCliente);
}

int JuegoCliente::obtenerIDPropio() const{
	return idPropio;
}

std::map<int,jugador_t> JuegoCliente::obtenerJugadores(){
	return jugadores;
}

bool JuegoCliente::enRango(int posX, int w) const {
    return (rectanguloCamara.x - RANGO_VISTA) <= posX + w && posX <= (rectanguloCamara.x + anchoVista + RANGO_VISTA);
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

void JuegoCliente::agregarPodios(ultimos_podios_t ultimos_podios){
    pthread_mutex_lock(&mutexJuegoCliente);
    podios.push_back(ultimos_podios.podioUltimoNivel);
    nivelesJugados++;
    podioPuntosTotales = ultimos_podios.podioAcumulado;
    pthread_mutex_unlock(&mutexJuegoCliente);
}

void JuegoCliente::agregarNivel(nivel_t nivel) {
    pthread_mutex_lock(&mutexJuegoCliente);
    if(numeroMundo != NO_HAY_MUNDO_CARGADO){
        this->hayQueMostrarPuntosDeNivel = true;
    }
    numeroMundo = nivel.mundo;

    cargarLista(&ladrillos,nivel.bloques,nivel.topeBloques);
    cargarLista(&entidades[TUBERIA], nivel.tuberias, nivel.topeTuberias);
    cargarLista(&entidades[POZO], nivel.pozos, nivel.topePozos);
    crearListaDeFondoPozo(&entidades[FONDO_POZO], nivel.pozos, nivel.topePozos);

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

void JuegoCliente::dejarDeMostrarPuntosNivel() {
    this->hayQueMostrarPuntosDeNivel = false;
}

bool JuegoCliente::hayQueMostrarPuntosNivel() {
    return this->hayQueMostrarPuntosDeNivel;
}

std::list<entidad_t> JuegoCliente::obtenerEntidad(int claveEntidad) {
    if(claveEntidad == TUBERIA || claveEntidad == POZO || claveEntidad == FONDO_POZO){
        std::list<entidad_t> entidadesAMostrar;
        for(auto entidad:entidades[claveEntidad]){
            if(enRango(entidad.x, ANCHO_POZO)){ // Se utiliza el ancho del pozo porque es el mas grande de los 2
                entidadesAMostrar.push_front(entidad);
            }
        }
        return entidadesAMostrar;
    }
    return entidades[claveEntidad];
}


