#include "Botonera.hpp"

Botonera* Botonera::botonera = nullptr;

Botonera* Botonera::getInstance() {
    if(botonera == nullptr){
        botonera = new Botonera();
    }
    return botonera;
}

void Botonera::agregarSonido(uint8_t claveSonido, int idDetonante) {
    sonido_t sonido;
    sonido.tipoSonido = claveSonido;
    if(esUnSonidoValido(sonido)){
        sonidos[idDetonante].push_back(sonido);
    }
}

std::list<sonido_t> Botonera::obtenerSonidosDe(int idDetonante) {
    std::list<sonido_t> retorno = sonidos[idDetonante];
    sonidos[idDetonante].clear();
    return retorno;
}