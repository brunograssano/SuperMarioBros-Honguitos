#include "Pozo.hpp"

Pozo::Pozo(int posX, int tipo) {
    this->posicionX =  posX;
    this->tipo = tipo;
}

unsigned short Pozo::obtenerPosicionX() const {
    return posicionX;
}

pozo_t Pozo::serializar(){
    return {posicionX,tipo};
}