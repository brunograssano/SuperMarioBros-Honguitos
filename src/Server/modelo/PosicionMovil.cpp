#include "PosicionMovil.hpp"

PosicionMovil::PosicionMovil(int coordenadaX, int coordenadaY, int minimoY, int minimoX, int maximoX) : Posicion() {
    this->posicionX= (float)coordenadaX;
    this->posicionY= (float)coordenadaY;
    this->minimoY = minimoY;
    this->minimoX = minimoX;
    this->maximoX = maximoX;
}

PosicionMovil::PosicionMovil(int coordenadaX, int coordenadaY) : Posicion() {
    this->posicionX= (float) coordenadaX;
    this->posicionY= (float)coordenadaY;
    this->minimoY = -2147483647;
    this->minimoX = -2147483648;
    this->maximoX = 2147483647;
}

void PosicionMovil::moverHorizontal(float cantidadAMover) {
    if(((posicionX + cantidadAMover) <= (float)maximoX) && ((posicionX + cantidadAMover) >= (float)minimoX))
        this->posicionX+=cantidadAMover;
}

void PosicionMovil::moverVertical(float cantidadAMover) {
    if(((posicionY + cantidadAMover) >= (float)minimoY))
        this->posicionY+=cantidadAMover;
    else
        this->posicionY=(float)minimoY;
}

void PosicionMovil::actualizarLimiteTerrenoIzq(int limite) {
    minimoX = limite;
}

void PosicionMovil::actualizarLimiteTerrenoDer(int limite) {
    maximoX = limite;
}

void PosicionMovil::reiniciar(const Posicion& pos) {
    posicionX = (float)pos.obtenerPosX();
    posicionY = (float)pos.obtenerPosY();
}
