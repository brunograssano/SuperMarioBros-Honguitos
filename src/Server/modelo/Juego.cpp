

#include "Juego.hpp"

#include <utility>

Juego* Juego::instanciaJuego = nullptr;

void Juego::inicializar() {} //todo: ¿?

Juego* Juego::getInstance(){
	return instanciaJuego;
}

Juego* Juego::getInstance(list<Nivel*> niveles,int cantJugadores){
	if(instanciaJuego==nullptr){
		instanciaJuego = new Juego(std::move(niveles),cantJugadores);
	}
	return instanciaJuego;
}

void Juego::avanzarNivel(Camara* camara){
    if(niveles.empty()) return;

    Nivel* nivelViejo = niveles.front();
    int puntos = nivelViejo->tiempoRestante(); //todo: cambiarlo
    delete nivelViejo;
    niveles.pop_front();

    if(niveles.empty()){
        hanGanado = true;
        sumarPuntosAJugadores(puntos);
        Log::getInstance()->mostrarMensajeDeInfo("Se terminaron los niveles del juego");
    }
    else{
        camara->reiniciar();
        sumarPuntosAJugadores(puntos);
        niveles.front()->iniciar();
        for(auto const& parClaveJugador:jugadores){
            parClaveJugador.second->reiniciarPosicion();
        }
        Log::getInstance()->mostrarMensajeDeInfo("Se avanzo de nivel");
    }
}

void Juego::desconectarJugador(int idJugador){
	jugadores[idJugador]->desconectar();
}

void Juego::conectarJugador(int idMarioConectandose){
	jugadores[idMarioConectandose]->conectar();
}

list<Enemigo*> Juego::obtenerEnemigos(){
    if(niveles.empty()) return list<Enemigo*>();
	return niveles.front()->obtenerEnemigos();
}

list<Plataforma*> Juego::obtenerPlataformas(){
    if(niveles.empty()) return list<Plataforma*>();
	return niveles.front()->obtenerPlataformas();
}

list<Moneda*> Juego::obtenerMonedas(){
    if(niveles.empty()) return list<Moneda*>();
	return niveles.front()->obtenerMonedas();
}

list<Tuberia*> Juego::obtenerTuberias() {
    if(niveles.empty()) return list<Tuberia*>();
    return niveles.front()->obtenerTuberias();
}

int Juego::obtenerTiempoRestante(){
    if(niveles.empty()) return 0;
    return niveles.front()->tiempoRestante();
}

void Juego::actualizarModelo(Camara* camara){
    if(niveles.empty()) return;

    for(auto const& parClaveJugador:jugadores){
        parClaveJugador.second->actualizarPosicion();
    }
    Nivel* nivelActual = niveles.front();
	nivelActual->actualizarModelo();

    if(todosEnLaMeta()) {
        avanzarNivel(camara /*TODO: Sacar estos parametros*/);
    }
    camara->moverCamara(this->jugadores);
}

void Juego::sumarPuntosAJugadores(int puntos){

	for(auto const& parClaveJugador:jugadores){
		if(parClaveJugador.second->estaConectado()){
			parClaveJugador.second->agregarPuntos(puntos);
		}
	}
}

int Juego::obtenerMundoActual(){
    if(niveles.empty()) return 0;
    return niveles.front()->obtenerMundo();
}

Juego::~Juego(){

	for(auto const& parClaveJugador:jugadores){
		delete parClaveJugador.second;
	}
	for(auto const& nivel:niveles){
		delete nivel;
	}
	jugadores.clear();
	niveles.clear();
}

void Juego::actualizarJugador(unsigned short idJugador, entrada_usuario_t entradaUsuario) {

    Mario* jugador = jugadores[idJugador];
    bool seMovio = false;
    if(entradaUsuario.A){
        jugador->actualizarIzquierdaMario();
        seMovio = true;
    }
    if(entradaUsuario.D){
        jugador->actualizarDerechaMario();
        seMovio = true;
    }
    if(entradaUsuario.W){
        jugador->actualizarSaltarMario();
        seMovio = true;
    }
    if(entradaUsuario.S && !seMovio){
        jugador->actualizarAgacharseMario();
    }
}

bool Juego::todosEnLaMeta() {
    if(niveles.empty()) return false;

    bool alguienConectado = false;
    bool todosEnLaMeta = true;
    int puntoBandera = niveles.front()->obtenerPuntoBanderaFin();
    for(auto const& parClaveJugador:jugadores){
        Mario* jugador = parClaveJugador.second;
        if(jugador->estaConectado()){
            alguienConectado = true;
            if(jugador->obtenerPosicionX() < puntoBandera){
                todosEnLaMeta = false;
            }
        }
    }
    return todosEnLaMeta && alguienConectado;
}

bool Juego::ganaron() {
    return hanGanado;
}

void Juego::iniciar(){
    if(niveles.empty()) return;
    niveles.front()->iniciar();
}

bool Juego::perdieron() {
    return ((obtenerTiempoRestante() == 0) && !ganaron());
}

info_partida_t Juego::obtenerInfoPartida(map<int,string> mapaIDNombre, int IDJugador, Camara* camara){
    info_partida_t info_partida;
    memset(&info_partida,0,sizeof(info_partida_t));

    info_partida.altoVentana =  camara->obtenerRectanguloCamara().h;
    info_partida.anchoVentana = camara->obtenerRectanguloCamara().w;
    info_partida.cantidadJugadores = jugadores.size();
    info_partida.idPropio = IDJugador;

    for(int i=0;i<jugadores.size();i++){
        info_partida.jugadores[i].puntos = 0;
        info_partida.jugadores[i].mario.idImagen = i;
        info_partida.jugadores[i].mario.posX = jugadores[i]->obtenerPosicionX();
        info_partida.jugadores[i].mario.posY = jugadores[i]->obtenerPosicionY();
        info_partida.jugadores[i].mario.recorteImagen = jugadores[i]->obtenerSpite()->obtenerEstadoActual();
        strcpy(info_partida.jugadores[i].nombreJugador,mapaIDNombre[i].c_str());
    }

    int i = 0;
    for(auto& nivel:niveles){
        strcpy(info_partida.direccionesFondoNiveles[i], nivel->obtenerDireccionFondoActual().c_str());
        i++;
    }
    info_partida.cantidadFondosNiveles = i;

    info_partida.mundo = obtenerMundoActual();

    return info_partida;
}

info_ronda_t Juego::obtenerInfoRonda(map<int,string> mapaIDNombre, Camara* camara) {
    //TODO: Esto debería estar en parte en el nivel, así evitaríamos esos "obtenerBlaBla" y eso.
    info_ronda_t info_ronda;
    memset(&info_ronda,0,sizeof(info_ronda_t));

    info_ronda.mundo = obtenerMundoActual();
    info_ronda.posXCamara = camara->obtenerRectanguloCamara().x;
    info_ronda.tiempoFaltante = obtenerTiempoRestante();
    info_ronda.ganaron = ganaron();
    info_ronda.perdieron = perdieron();

    list<Plataforma*> plataformas = obtenerPlataformas();
    int numeroBloque = 0;
    for(auto const& plataforma: plataformas){
        list<bloque_t> bloques = plataforma->serializarPlataforma();

        for(auto const& bloque: bloques){
            if(camara->estaEnRangoVisible(bloque.posX) &&
               numeroBloque<MAX_BLOQUES){
                info_ronda.bloques[numeroBloque] = bloque;
                numeroBloque++;
            }
        }
    }
    info_ronda.topeBloques = numeroBloque;

    int numeroEnemigo = 0;
    list<Enemigo*> enemigos = obtenerEnemigos();
    for(auto const& enemigo: enemigos){
        if(camara->estaEnRangoVisible(enemigo->obtenerPosicionX()) &&
           numeroEnemigo<MAX_ENEMIGOS){
            info_ronda.enemigos[numeroEnemigo] = enemigo->serializar();
            numeroEnemigo++;
        }
    }
    info_ronda.topeEnemigos = numeroEnemigo;

    int numeroMoneda = 0;
    list<Moneda*> monedas = obtenerMonedas();
    for(auto const& moneda: monedas){
        if(camara->estaEnRangoVisible(moneda->obtenerPosicionX()) &&
           numeroMoneda<MAX_MONEDAS){
            info_ronda.monedas[numeroMoneda] = moneda->serializar();
            numeroMoneda++;
        }
    }
    info_ronda.topeMonedas = numeroMoneda;

    jugador_t jugadorSerializado;
    for(int i=0; i<jugadores.size(); i++){
        jugadorSerializado = jugadores[i]->serializar(mapaIDNombre[i].c_str(), i);
        info_ronda.jugadores[i] = jugadorSerializado;
    }

    list<Tuberia*> tuberias = obtenerTuberias();
    int numeroTuberia = 0;
    for(auto const& tuberia: tuberias){
        if(camara->estaEnRangoVisible(tuberia->obtenerPosicionX()) &&
           numeroTuberia<MAX_TUBERIAS){
            info_ronda.tuberias[numeroTuberia] = tuberia->serializar();
            numeroTuberia++;
        }
    }
    info_ronda.topeTuberias = numeroTuberia;

    return info_ronda;
}

bool Juego::hayConectados() {
    int i = 0;
    bool hayAlguienConectado = false;
    while(i<jugadores.size() && !hayAlguienConectado){
        if(jugadores[i]->estaConectado()){
            hayAlguienConectado = true;
        }
        i++;
    }
    return hayAlguienConectado;

}
