#include "MovimientoHorizontalIdeal.hpp"

MovimientoHorizontalIdeal::MovimientoHorizontalIdeal(float velocidad) {
    velocidadX = velocidad;
}

void MovimientoHorizontalIdeal::mover(PosicionMovil *posicion) {
    posicion->moverHorizontal(velocidadX);
}

void MovimientoHorizontalIdeal::setVelocidad(float velocidad) {
    velocidadX = velocidad;
}

void MovimientoHorizontalIdeal::cambiarDireccion() {
    velocidadX = -velocidadX;
}

bool MovimientoHorizontalIdeal::debeEspejarse() const {
    return velocidadX > 0;
}
