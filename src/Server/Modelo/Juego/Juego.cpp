#include "src/Utils/log/Log.hpp"
#include "Juego.hpp"

Juego* Juego::instanciaJuego = nullptr;

Juego::Juego(std::list<Nivel *> nivelesLector, int cantJugadores, int alto_pantalla, int ancho_pantalla)
      : camara(alto_pantalla, ancho_pantalla){
    for(int i = 0; i < cantJugadores; i++){
        jugadores[i] = new Mario(i);
    }

    seGuardoUltimoPodio = false;

    niveles = std::move(nivelesLector);

    for (auto const& nivel : niveles) {
        nivel->inicializar();
    }

    hanGanado = false;
}


Juego* Juego::getInstance(){
	return instanciaJuego;
}

Juego* Juego::getInstance(std::list<Nivel*> niveles,int cantJugadores, int alto_pantalla, int ancho_pantalla){
	if(instanciaJuego==nullptr){
		instanciaJuego = new Juego(std::move(niveles),cantJugadores, alto_pantalla, ancho_pantalla);
	}
	return instanciaJuego;
}

void Juego::avanzarNivel(){
    if(niveles.empty()) return;

    Nivel* nivelViejo = niveles.front();

    nivelViejo->terminar(this->jugadores);
    guardarPodio(nivelViejo->obtenerPodio());

    delete nivelViejo;
    niveles.pop_front();

    if(!niveles.empty()){
        camara.reiniciar();
        niveles.front()->iniciar(jugadores);
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
	nivelActual->actualizarModelo(jugadores, camara.obtenerRectanguloCamara());

    if( !murieronTodos() && hayConectados() && nivelActual->todosEnLaMeta(jugadores)) {
        avanzarNivel();
        revisarSiGanaronElJuego();
    }

    if(perdieron()){
        if(!seGuardoUltimoPodio) {
            guardarPodio(niveles.front()->obtenerPodio());
            seGuardoUltimoPodio = true;
        }
    }

    camara.moverCamara(this->jugadores);
}

int Juego::obtenerMundoActual(){
    if(niveles.empty()) return 0;
    return niveles.front()->obtenerMundo();
}

void Juego::actualizarJugador(unsigned short idJugador, entrada_usuario_t entradaUsuario) {
    if(niveles.empty()) return;

    Mario* jugador = jugadores[idJugador];
    if(!jugador->estaVivo()){return;}

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
    if(entradaUsuario.T){
        jugador->alternarModoTest();
    }
    if(entradaUsuario.ESP){
        ObjetoFugaz* disparo = jugador->dispararFuego();
        niveles.front()->aparecerDisparo(disparo);
    }
}

bool Juego::ganaron() const {
    return hanGanado;
}

void Juego::iniciar(){
    if(niveles.empty()) return;
    niveles.front()->iniciar(jugadores);
}

bool Juego::perdieron() {
    return ((obtenerTiempoRestante() == 0) && !ganaron()) || murieronTodos();
}

info_partida_t Juego::obtenerInfoPartida(std::map<int,std::string> mapaIDNombre, int IDJugador){
    info_partida_t info_partida;
    memset(&info_partida,0,sizeof(info_partida_t));

    info_partida.altoVentana =  camara.obtenerRectanguloCamara().h;
    info_partida.anchoVentana = camara.obtenerRectanguloCamara().w;
    info_partida.cantidadJugadores = jugadores.size();
    info_partida.idPropio = IDJugador;

    int indicePodio = 0;
    if(!podios.empty()) {
        for (auto const &podio: podios) {
            info_partida.podios[indicePodio] = podio;
            indicePodio++;
        }
        info_partida.podioPuntosAcumulados = this->podioAcumulado;
    }
    info_partida.topePodios = indicePodio;


    for(int i=0;i<jugadores.size();i++){
        info_partida.jugadores[i].mario.puntos = 0;
        info_partida.jugadores[i].mario.idImagen = i;
        info_partida.jugadores[i].mario.posX = jugadores[i]->obtenerPosicionX();
        info_partida.jugadores[i].mario.posY = jugadores[i]->obtenerPosicionY();
        info_partida.jugadores[i].mario.recorteImagen = jugadores[i]->obtenerEstadoActual();
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

info_ronda_t Juego::obtenerInfoRonda() {
    info_ronda_t info_ronda;
    memset(&info_ronda,0,sizeof(info_ronda_t));

    info_ronda.posXCamara = camara.obtenerRectanguloCamara().x1;
    info_ronda.ganaron = ganaron();
    info_ronda.perdieron = perdieron();

    for(int i=0; i<jugadores.size(); i++){
        info_ronda.jugadores[i] = jugadores[i]->serializar(i);
    }

    if(!niveles.empty())
        niveles.front()->completarInformacionRonda(&info_ronda, Camara::estaEnRangoHelper, &camara);
    return info_ronda;
}

podio_t Juego::obtenerUltimoPodio(){
    return this->podios.back();
}

podio_t Juego::obtenerPodioAcumulado(){
    return this->podioAcumulado;
}

nivel_t Juego::serializarNivel(){
    nivel_t nivel;
    memset(&nivel,0,sizeof(nivel_t));

    if(!niveles.empty())
        niveles.front()->completarInformacionNivel(&nivel);

    if(!podios.empty()){
        nivel.podio = this->podios.back();
        nivel.podioPuntosAcumulados = this->podioAcumulado;
    }

    return nivel;
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

int Juego::cantidadDeNiveles() {
    return niveles.size();
}

bool Juego::murieronTodos() {
    for(auto const& parClaveJugador:jugadores){
        if(parClaveJugador.second->estaVivo()){
            return false;
        }
    }
    return true;
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

void Juego::guardarPodio(Podio *podio) {
    podio_t podioSerializado;
    podioSerializado.cantidadJugadores = 0;
    podioSerializado.nivel = this->niveles.front()->obtenerMundo();
    int cantidadJugadores = podio->getPodioNivel().size();
    for(int indiceJugador = 0; indiceJugador < cantidadJugadores; indiceJugador++) {
        podioSerializado.puntosNivel[indiceJugador] = podio->getPodioNivel().at(indiceJugador).second;
        podioSerializado.ids[indiceJugador] = podio->getPodioNivel().at(indiceJugador).first->obtenerNumeroJugador();
        podioSerializado.cantidadJugadores++;
    }
    this->podios.push_back(podioSerializado);

    podioAcumulado.cantidadJugadores = 0;
    podioAcumulado.nivel = this->niveles.front()->obtenerMundo();

    for(int indiceJugador = 0; indiceJugador < cantidadJugadores; indiceJugador++){
        this->podioAcumulado.puntosNivel[indiceJugador] = podio->getPodioTotal().at(indiceJugador).second;
        this->podioAcumulado.ids[indiceJugador] = podio->getPodioTotal().at(indiceJugador).first->obtenerNumeroJugador();
        this->podioAcumulado.cantidadJugadores++;
    }
}

void Juego::revisarSiGanaronElJuego() {
    if(niveles.empty()){
        hanGanado = true;
        Log::getInstance()->mostrarMensajeDeInfo("Se terminaron los niveles del juego");
    }
}
