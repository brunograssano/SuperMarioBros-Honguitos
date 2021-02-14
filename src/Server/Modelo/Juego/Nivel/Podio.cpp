#include <algorithm>
#include "Podio.hpp"
using namespace std;

void Podio::recibirJugadores(const map<int, Mario *>& jugadores) {
    for(auto parJugador:jugadores){
        puntajeParcial.emplace_back(parJugador.second,0);
        puntajeNivelAnterior.emplace_back(parJugador.second,parJugador.second->obtenerPuntos());
        puntajeTotal.emplace_back(parJugador.second, parJugador.second->obtenerPuntos());
    }
}

int buscarIndicePar(Mario * mario,vector<pair<Mario*, int>> vector){
    int indice;
    for (int i = 0; i < vector.size(); ++i) {
       if (vector.at(i).first == mario){
           indice = i;
       }
    }
    return indice;
}

void Podio::actualizar(Observable* mario){
    int puntosTotales = ((Mario *)mario)->obtenerPuntos();
    int indicePuntajeParcial = buscarIndicePar((Mario *)mario,puntajeParcial);
    int indicePuntajeAnterior = buscarIndicePar((Mario *)mario,puntajeNivelAnterior);
    int indicePuntajeTotal = buscarIndicePar((Mario *) mario, puntajeTotal);
    puntajeParcial.at(indicePuntajeParcial).second = puntosTotales - puntajeNivelAnterior.at(indicePuntajeAnterior).second;
    puntajeTotal.at(indicePuntajeTotal).second = puntosTotales;
}

auto comparadorParcial = [](pair<Mario*, int> const & primerElemento, pair<Mario*, int> const & segundoElemento){
    return primerElemento.second > segundoElemento.second;
};

auto comparadorTotal = [](pair<Mario*, int> const & primerElemento, pair<Mario*, int> const & segundoElemento){
    return primerElemento.first->obtenerPuntos() != segundoElemento.first->obtenerPuntos() ? primerElemento.first->obtenerPuntos() > segundoElemento.first->obtenerPuntos() : primerElemento.first > segundoElemento.first;
};

vector<pair<Mario*, int>> Podio::getPodioNivel() {
    sort(puntajeParcial.begin(), puntajeParcial.end(), comparadorParcial);
    return puntajeParcial;
}

vector<pair<Mario* , int>> Podio::getPodioTotal() {
    sort(puntajeTotal.begin(), puntajeTotal.end(), comparadorTotal);
    return puntajeTotal;
}



