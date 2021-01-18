#include <cstdlib>
#include "MovimientoEnemigo.hpp"
#include <cmath>
#define FUERZA_SALTO_ENEMIGO 0

MovimientoEnemigo::MovimientoEnemigo() {
    movimientoVertical = MovimientoVertical(FUERZA_SALTO_ENEMIGO);
    movimientoHorizontal = MovimientoHorizontalIdeal(obtenerVelocidad());
}

void MovimientoEnemigo::mover(PosicionMovil *posicionMovil) {
    movimientoHorizontal.mover(posicionMovil);
    movimientoVertical.mover(posicionMovil);
}

float MovimientoEnemigo::obtenerVelocidad() {
    return (0.2 + ((rand() % 11) / 100)) * pow(-1,rand()%2);
}

bool MovimientoEnemigo::debeEspejarse() {
    return movimientoHorizontal.debeEspejarse();
}

void MovimientoEnemigo::morir() {
    movimientoHorizontal.setVelocidad(0);
}

void MovimientoEnemigo::cambiarOrientacion() {
    movimientoHorizontal.cambiarDireccion();
}

void MovimientoEnemigo::setVelocidadY(const float velocidadY) {
    movimientoVertical.setVelocidadY(velocidadY);
}
