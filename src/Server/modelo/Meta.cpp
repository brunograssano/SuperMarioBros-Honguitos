#include <algorithm>
#include "Meta.hpp"
#include "src/Server/Botonera/Botonera.hpp"

Meta::Meta(int puntoBandera) {
    this->puntoBandera = puntoBandera;
}

void Meta::agregarSiPasoLaMeta(Mario *jugador) {
    if(!yaLLegoALaMeta(jugador) && estaEnLaMeta(jugador) && jugador->estaConectado() && jugador->estaVivo()){
        ganadores.push_back(jugador);
        Botonera::getInstance()->agregarSonido(SONIDO_LLEGAR_A_LA_META, jugador->obtenerID());
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
    return (!jugador->estaConectado() || !jugador->estaVivo()) || jugador->obtenerPosicionX() >= puntoBandera;
}

bool Meta::todosEnLaMeta(const std::map<int, Mario *>& jugadores) {
    if(todosDesconectados(jugadores)){
        return false;
    }
    else if(conectadosMuertosYDesconectadosVivos(jugadores)){
        return false;
    }
    return conectadosVivosPasaronMetaYDesconectadosNo(jugadores);
}

bool Meta::conectadosVivosPasaronMetaYDesconectadosNo(const map<int, Mario *> &jugadores) {
    bool pasaronMeta = true;
    const int cantidadJugadores = jugadores.size();
    auto iterador = jugadores.begin();
    int i = 0;
    while(i<cantidadJugadores && pasaronMeta){
        if(!estaEnLaMeta(iterador->second)){
            pasaronMeta = false;
        }
        std::advance(iterador, 1);
        i++;
    }
    return pasaronMeta;
}

bool Meta::todosDesconectados(const map<int, Mario *> &jugadores) {
    return std::all_of(jugadores.begin(), jugadores.end(),[](auto parClaveJugador){return !parClaveJugador.second->estaConectado();});
}

bool Meta::conectadosMuertosYDesconectadosVivos(const map<int, Mario *> &jugadores) {
    list<Mario*> jugadoresConectados;
    list<Mario*> jugadoresDesconectados;
    for(auto parClaveJugador:jugadores){
        if(parClaveJugador.second->estaConectado()){
            jugadoresConectados.push_back(parClaveJugador.second);
        }
        else{
            jugadoresDesconectados.push_back(parClaveJugador.second);
        }
    }
    return std::all_of(jugadoresConectados.begin(),jugadoresConectados.end(),[](Mario* jugador){return !jugador->estaVivo();}) &&
            std::any_of(jugadoresDesconectados.begin(),jugadoresDesconectados.end(),[](Mario* jugador){return jugador->estaVivo();});
}