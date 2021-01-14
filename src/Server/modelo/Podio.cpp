#include <algorithm>
#include <vector>
#include "Podio.hpp"
using namespace std;

void Podio::recibirJugadores(map<int, Mario *> jugadores) {
    for (auto& elemento : jugadores) {
        puntajeTotal.push_back(elemento);
    }
    for(auto parJugador:jugadores){
        puntajeParcial.push_back(make_pair(parJugador.second,0));
        puntajeNivelAnterior.push_back(make_pair(parJugador.second,parJugador.second->obtenerPuntos()));
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
    puntajeParcial.at(indicePuntajeParcial).second = puntosTotales - puntajeNivelAnterior.at(indicePuntajeAnterior).second;
}

auto comparadorParcial = [](pair<Mario*, int> const & primerElemento, pair<Mario*, int> const & segundoElemento){
    return primerElemento.second > segundoElemento.second;
};

auto comparadorTotal = [](pair<int, Mario*> const & primerElemento, pair<int, Mario*> const & segundoElemento){
    return primerElemento.second->obtenerPuntos() != segundoElemento.second->obtenerPuntos() ? primerElemento.second->obtenerPuntos() > segundoElemento.second->obtenerPuntos() : primerElemento.first > segundoElemento.first;
};

vector<pair<Mario*, int>> Podio::getPodioNivel() {
    sort(puntajeParcial.begin(), puntajeParcial.end(), comparadorParcial);
    return puntajeParcial;
}

vector<pair<int,Mario*>> Podio::getPodioTotal() {
    sort(puntajeTotal.begin(), puntajeTotal.end(), comparadorTotal);
    return puntajeTotal;
}



