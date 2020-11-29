

#include "Juego.hpp"

Juego* Juego::instanciaJuego = nullptr;

void Juego::inicializar(int cantJugadores){


}

Juego* Juego::getInstance(){
	return instanciaJuego;
}

Juego* Juego::getInstance(list<Nivel*> niveles,int cantJugadores){
	if(instanciaJuego==nullptr){
		instanciaJuego = new Juego(niveles,cantJugadores);
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

void Juego::actualizarPosicionesEnemigos(){
	Nivel* nivelActual = niveles.front();
	nivelActual->actualizarPosicionesEnemigos();
}

void Juego::sumarPuntosAJugadores(int puntos){
	for(auto const& parClaveJugador:jugadores){
		parClaveJugador.second->agregarPuntos(puntos);
	}
}

string Juego::obtenerDireccionFondoNivelActual(){
	Nivel* nivelActual = niveles.front();
	return nivelActual->obtenerDireccionFondoActual();
}

int Juego::obtenerTiempoDelNivel(){
	Nivel* nivelActual = niveles.front();
	return nivelActual->obtenerTiempo();
}

int Juego::obtenerPuntuacionJugador(){
	return 1;//jugador->obtenerPuntos();
}

int Juego::obtenerMundoActual(){
	Nivel* nivelActual = niveles.front();
	return nivelActual->obtenerMundo();
}

int Juego::obtenerPuntoBanderaFinActual(){
	Nivel* nivelActual = niveles.front();
	return nivelActual->obtenerPuntoBanderaFin();
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
