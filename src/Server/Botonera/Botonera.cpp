#include "Botonera.hpp"
#include <cstring>

Botonera* Botonera::botonera=nullptr;

Botonera* Botonera::getInstance() {
    if(botonera==nullptr){
        botonera = new Botonera();
    }
    return botonera;
}

void Botonera::agregarSonido(std::string claveSonido, int idDetonante) {
    if(claveSonido.empty()) return;
    sonido_t sonido;
    strcpy(sonido.nombre, claveSonido.c_str());
    sonidos[idDetonante].push_back(sonido);
}

std::list<sonido_t> Botonera::obtenerSonidosDe(int idDetonante) {
    std::list<sonido_t> retorno = sonidos[idDetonante];
    sonidos[idDetonante].clear();
    return retorno;
}