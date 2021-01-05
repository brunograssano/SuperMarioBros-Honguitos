#include "Bloque.hpp"

int Bloque::obtenerPosicionX() {
    return this->posicion->obtenerPosX();
}

int Bloque::obtenerPosicionY() {
    return this->posicion->obtenerPosY();
}

Sprite *Bloque::obtenerSprite() {
    return this->spriteBloque;
}

void Bloque::ubicarEnPosicionDefault() {
    delete this->posicion;
    this->posicion = new PosicionFija(200, 200);
}

ObjetoSorpresa* Bloque::colisionaronAbajo() {
    return new SinSorpresa();
}

int Bloque::normalizarCoordenadaIngresada(int coordenada) {
    return (coordenada/40)*40;
}

bloque_t Bloque::serializar() {
    bloque_t bloqueSerializado = {0, 0, 0, 0};
    bloqueSerializado.posX = posicion->obtenerPosX();
    bloqueSerializado.posY = posicion->obtenerPosY();
    bloqueSerializado.numeroRecorteX = spriteBloque->obtenerEstadoActual();
    bloqueSerializado.numeroRecorteY = tipoBloque;
    return bloqueSerializado;
}
