#include "Moneda.hpp"


Moneda::Moneda(int coordenadaX, int coordenadaY) {
    this->posicion = new PosicionFija(coordenadaX, coordenadaY);
    this->sprite = new SpriteMoneda();
}

Moneda::~Moneda() {
    delete this->posicion;
    delete this->sprite;
}

void Moneda::actualizar() {
    this->sprite->actualizarSprite();
}

moneda_t Moneda::serializar() {
    moneda_t monedaSerializada;

    monedaSerializada.posX = posicion->obtenerPosX();
    monedaSerializada.posY = posicion->obtenerPosY();
    monedaSerializada.numeroRecorte = sprite->obtenerEstadoActual();
    return monedaSerializada;
}

int Moneda::obtenerPosicionX() {
    return this->posicion->obtenerPosX();
}

int Moneda::obtenerPosicionY() {
    return this->posicion->obtenerPosY();
}
