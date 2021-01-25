#include "Pozo.hpp"

Pozo::Pozo(int posicionX, int tipo, int fondo) {
    this->posicionX =  posicionX;
    this->tipo = tipo;
    this->fondo = fondo;
}

unsigned short Pozo::obtenerPosicionX() const {
    return posicionX;
}

pozo_t Pozo::serializar(){
    return {posicionX,fondo,tipo};
}