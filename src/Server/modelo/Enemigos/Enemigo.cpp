#include "Enemigo.hpp"

int Enemigo::obtenerPosicionX() {
    return posicionActual->obtenerPosX();
}

int Enemigo::obtenerPosicionY() {
    return posicionActual->obtenerPosY();
}

void Enemigo::agregarPosicion(int coordenadaX, int coordenadaY) {
    posicionActual = new PosicionMovil(coordenadaX,coordenadaY);
}

void Enemigo::actualizarPosicion() {
    posicionActual->moverHorizontal(velocidadX);
    spriteEnemigo->actualizarSprite();
}

void Enemigo::morir(Mario* marioQueMatoAlEnemigo) {
    marioQueMatoAlEnemigo->agregarPuntos(puntos);
    spriteEnemigo->morir();
}