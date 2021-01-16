#include "Piso.hpp"
#include "Plataforma.hpp"

#define COMIENZO_PISO 0
#define FIN_PISO 10000

Piso::Piso(int altoPiso) {
    alto = altoPiso;
}

void Piso::agregarPozo(int posicionPozo, int tipoPozo, int fondo) {
    auto pozo = Pozo(posicionPozo, tipoPozo, fondo);
    pozos.push_back(pozo);
}

void Piso::inicializar() {
    int comienzoPlataforma = COMIENZO_PISO;
    for(auto pozo:pozos){
        int comienzoPozo = pozo.obtenerPosicionX();
        if(comienzoPlataforma<comienzoPozo){
            plataformas.push_front(new Plataforma(comienzoPlataforma,comienzoPozo,alto));
        }
        comienzoPlataforma = comienzoPozo + ANCHO_POZO;
    }
    if(comienzoPlataforma<FIN_PISO){
        plataformas.push_front(new Plataforma(comienzoPlataforma,FIN_PISO,alto));
    }
}

list<Colisionable*> Piso::obtenerPiso() {
    return plataformas;
}

list<pozo_t> Piso::serializar() {
    list<pozo_t> pozosSerializados;
    for(auto pozo: pozos){
        pozo_t pozo_serializado = pozo.serializar();
        pozosSerializados.push_back(pozo_serializado);
    }
    return pozosSerializados;
}

Piso::~Piso() {
    for(auto plataforma:plataformas){
        delete plataforma;
    }
}

int Piso::obtenerAltura() {
    return alto;
}
