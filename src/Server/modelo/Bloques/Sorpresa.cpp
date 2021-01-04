#include "Sorpresa.hpp"

Sorpresa::Sorpresa(int coordenadaX, int coordenadaY) {
    int coordenadaXNormalizada = normalizarCoordenadaIngresada(coordenadaX);
    int coordenadaYNormalizada = normalizarCoordenadaIngresada(coordenadaY);
    this->posicion = new PosicionFija(coordenadaXNormalizada, coordenadaYNormalizada);
    this->spriteBloque = new SpriteSorpresa();
}

bloque_t Sorpresa::serializar() {
    bloque_t bloqueSerializado = {0, 0, 0, 0};
    bloqueSerializado.posX = posicion->obtenerPosX();
    bloqueSerializado.posY = posicion->obtenerPosY();
    bloqueSerializado.numeroRecorteX = spriteBloque->obtenerEstadoActual();
    bloqueSerializado.numeroRecorteY = SORPRESA;
    return bloqueSerializado;
}

Sorpresa::~Sorpresa() {
    delete this->posicion;
    delete this->spriteBloque;
}