#include <cstdlib>
#include "MovimientoEnemigo.hpp"
#include <cmath>
#define FUERZA_SALTO_ENEMIGO 0
#define VELOCIDAD_MINIMA 0.2
#define RANGO_VELOCIDAD_EXTRA 11

#define NORMALIZACION 100

MovimientoEnemigo::MovimientoEnemigo(float velocidadExtra) {
    movimientoVertical = MovimientoVertical(FUERZA_SALTO_ENEMIGO);
    float velocidadEnX = obtenerVelocidad(velocidadExtra);
    movimientoHorizontal = MovimientoHorizontalIdeal(velocidadEnX);
}

void MovimientoEnemigo::mover(PosicionMovil *posicionMovil) {
    movimientoHorizontal.mover(posicionMovil);
    movimientoVertical.mover(posicionMovil);
}

float MovimientoEnemigo::obtenerVelocidad(float velocidadExtra) {
    return ( (float)pow(-1,rand()%2) * (float)(VELOCIDAD_MINIMA + velocidadExtra + (float)((float)(rand() % RANGO_VELOCIDAD_EXTRA) / NORMALIZACION) ) );
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
