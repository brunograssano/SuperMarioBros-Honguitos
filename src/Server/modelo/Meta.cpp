#include "Meta.hpp"

Meta::Meta(int puntoBandera) {
    this->puntoBandera = puntoBandera;
}

void Meta::agregarSiPasoLaMeta(Mario *jugador) {
    if(!yaLLegoALaMeta(jugador) && estaEnLaMeta(jugador) && jugador->estaConectado()){
        ganadores.push_back(jugador);
    }
}

void Meta::sumarPuntos(int puntosExtra) {
    int i = 0;
    for(auto const& jugador:ganadores){
        jugador->agregarPuntos(MAX_PUNTOS - RESTA_PUNTOS*i + puntosExtra);
        i++;
    }
    ganadores.clear();
}

bool Meta::yaLLegoALaMeta(Mario *jugador) {
    for(auto const& ganador:ganadores){
        if(ganador == jugador)
            return true;
    }
    return false;
}

Meta::~Meta() {
    ganadores.clear();
}

bool Meta::estaEnLaMeta(Mario* jugador) const {
    if(!jugador) return false;
    return (!jugador->estaConectado() || jugador->obtenerPosicionX() >= puntoBandera);
}

bool Meta::todosEnLaMeta(const std::map<int, Mario *>& mapaJugadores) {
    for(auto const& parClaveJugador:mapaJugadores){
        if(!estaEnLaMeta(parClaveJugador.second))
            return false;
    }
    return true;
}
