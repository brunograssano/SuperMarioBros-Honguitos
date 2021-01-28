#include "Pozo.hpp"

Pozo::Pozo(int posicionX, int tipo, int fondo) {
    this->posicionX =  posicionX;
    this->tipo = tipo;
    this->fondo = fondo;
}

unsigned short Pozo::obtenerPosicionX() const {
    return posicionX;
}

entidad_t Pozo::serializar() const{
    entidad_t pozoSerializado = {0,0,0,0,0,false};
    pozoSerializado.x = posicionX;
    pozoSerializado.recorteY = tipo; // Los tipos pinches, agua lava son de la misma imagen (recorte)
    pozoSerializado.tipo = fondo; // Usamos el tipo para elegir el fondo del pozo?
    return pozoSerializado;
}