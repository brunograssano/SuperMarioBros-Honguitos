

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

list<Nivel*> Juego::obtenerNiveles(){
	return niveles;
}

void Juego::avanzarNivel(SDL_Rect* rectanguloCamara){
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
        rectanguloCamara->x = 0;
        rectanguloCamara->y = 0;
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


map<int,Mario*> Juego::obtenerMarios(){
	return jugadores;
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

void Juego::actualizarModelo(SDL_Rect* camara/*TODO: Sacar estos parametros*/){
    if(niveles.empty()) return;

    for(auto const& parClaveJugador:jugadores){
        parClaveJugador.second->actualizarPosicion();
    }
    Nivel* nivelActual = niveles.front();
	nivelActual->actualizarModelo();

    if(todosEnLaMeta()) {
        avanzarNivel(camara /*TODO: Sacar estos parametros*/);
    }
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
