#include "Juego.hpp"

#include <utility>


Juego* Juego::instanciaJuego = nullptr;

void Juego::inicializar() {} //todo: ¿?

Juego* Juego::getInstance(){
	return instanciaJuego;
}

Juego* Juego::getInstance(list<Nivel*> niveles,int cantJugadores, int alto_pantalla, int ancho_pantalla){
	if(instanciaJuego==nullptr){
		instanciaJuego = new Juego(std::move(niveles),cantJugadores, alto_pantalla, ancho_pantalla);
	}
	return instanciaJuego;
}

void Juego::avanzarNivel(){
    if(niveles.empty()) return;

    Nivel* nivelViejo = niveles.front();
    nivelViejo->terminar();
    delete nivelViejo;
    niveles.pop_front();

    if(niveles.empty()){
        hanGanado = true;
        Log::getInstance()->mostrarMensajeDeInfo("Se terminaron los niveles del juego");
    }
    else{
        camara->reiniciar();
        niveles.front()->iniciar();
        Log::getInstance()->mostrarMensajeDeInfo("Se avanzo de nivel");
    }

    for(auto const& parClaveJugador:jugadores){
        parClaveJugador.second->reiniciarPosicion();
    }
}

void Juego::desconectarJugador(int idJugador){
	jugadores[idJugador]->desconectar();
}

void Juego::conectarJugador(int idMarioConectandose){
	jugadores[idMarioConectandose]->conectar();
}

int Juego::obtenerTiempoRestante(){
    if(niveles.empty()) return 0;
    return niveles.front()->tiempoRestante();
}

void Juego::actualizarModelo(){
    if(niveles.empty()) return;

    for(auto const& parClaveJugador:jugadores){
        parClaveJugador.second->actualizarPosicion();
    }
    Nivel* nivelActual = niveles.front();
	nivelActual->actualizarModelo(jugadores);

    if(nivelActual->todosEnLaMeta(jugadores) && hayConectados()) {
        avanzarNivel();
    }
    camara->moverCamara(this->jugadores);
}

int Juego::obtenerMundoActual(){
    if(niveles.empty()) return 0;
    return niveles.front()->obtenerMundo();
}

void Juego::actualizarJugador(unsigned short idJugador, entrada_usuario_t entradaUsuario) {
    if(niveles.empty()) return;

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
    if(entradaUsuario.F){
        jugador->hacerseDeFuego();
    }
    if(entradaUsuario.ESP){ //todo: tener un boton para esto je
        Disparo* disparo = jugador->dispararFuego();
        niveles.front()->aparecerDisparo(disparo);
    }
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

info_partida_t Juego::obtenerInfoPartida(map<int,string> mapaIDNombre, int IDJugador){
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

info_ronda_t Juego::obtenerInfoRonda(map<int,string> mapaIDNombre) {
    info_ronda_t info_ronda;
    memset(&info_ronda,0,sizeof(info_ronda_t));

    info_ronda.posXCamara = camara->obtenerRectanguloCamara().x;
    info_ronda.ganaron = ganaron();
    info_ronda.perdieron = perdieron();

    jugador_t jugadorSerializado;
    for(int i=0; i<jugadores.size(); i++){
        jugadorSerializado = jugadores[i]->serializar(mapaIDNombre[i].c_str(), i);
        info_ronda.jugadores[i] = jugadorSerializado;
    }


    if(!niveles.empty())
        niveles.front()->completarInformacionRonda(&info_ronda, Camara::estaEnRangoHelper, camara);
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

Juego::~Juego(){

    for(auto const& parClaveJugador:jugadores){
        delete parClaveJugador.second;
    }
    for(auto const& nivel:niveles){
        delete nivel;
    }
    jugadores.clear();
    niveles.clear();
    delete camara;
}