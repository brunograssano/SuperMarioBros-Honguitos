

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

void Juego::avanzarNivel(){
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

void Juego::actualizarModelo(){
	Nivel* nivelActual = niveles.front();
	nivelActual->actualizarModelo();
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

int Juego::obtenerPuntoBanderaFinActual(){
	return (int)niveles.front()->obtenerPuntoBanderaFin();
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

