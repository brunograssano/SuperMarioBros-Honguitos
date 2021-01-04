

#include "Juego.hpp"

#include <utility>

Juego* Juego::instanciaJuego = nullptr;

void Juego::inicializar() {}

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

void Juego::avanzarNivel(SDL_Rect* rectanguloCamara, Contador* contadorNivel){
    if(quedaSoloUnNivel()){
        sumarPuntosAJugadores(contadorNivel->tiempoRestante());
        Log::getInstance()->mostrarMensajeDeInfo("Se terminaron los niveles del juego");
    }
    else{
        rectanguloCamara->x= 0;
        rectanguloCamara->y = 0;
        sumarPuntosAJugadores(contadorNivel->tiempoRestante());
        delete contadorNivel;
        contadorNivel = new Contador(niveles.front()->obtenerTiempo(), SEGUNDOS);
        contadorNivel->iniciar();
        Log::getInstance()->mostrarMensajeDeInfo("Se avanzo de nivel");
    }

	Nivel* nivelViejo = niveles.front();
	delete nivelViejo;
	niveles.pop_front();
	for(auto const& parClaveJugador:jugadores){
		parClaveJugador.second->reiniciarPosicion();
	}
}

bool Juego::quedaSoloUnNivel(){
	return niveles.size()==1;
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
	return niveles.front()->obtenerEnemigos();
}

list<Plataforma*> Juego::obtenerPlataformas(){
	return niveles.front()->obtenerPlataformas();
}

list<Moneda*> Juego::obtenerMonedas(){
	return niveles.front()->obtenerMonedas();
}

list<Tuberia*> Juego::obtenerTuberias() {
    return niveles.front()->obtenerTuberias();
}

void Juego::actualizarModelo(SDL_Rect* camara, Contador* contador /*TODO: Sacar estos parametros*/){
    for(auto const& parClaveJugador:jugadores){
        parClaveJugador.second->actualizarPosicion();
    }
    Nivel* nivelActual = niveles.front();
	nivelActual->actualizarModelo();

    if(todosEnLaMeta()) {
        avanzarNivel(camara, contador /*TODO: Sacar estos parametros*/);
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
    bool alguienConectado = false;
    bool todosEnLaMeta = true;
    int puntoBandera = niveles.front()->obtenerPuntoBanderaFin();
    for(auto const& parClaveJugador:jugadores){
        Mario* jugador = parClaveJugador.second;
        if(jugador->estaConectado()){
            alguienConectado = true;
            if(jugador->obtenerPosicionX()<puntoBandera){
                todosEnLaMeta = false;
            }
        }
    }
    return todosEnLaMeta && alguienConectado;
}

bool Juego::ganaron() {
    return todosEnLaMeta() && quedaSoloUnNivel();
}

