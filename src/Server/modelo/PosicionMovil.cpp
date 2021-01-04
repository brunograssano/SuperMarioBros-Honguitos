#include "PosicionMovil.hpp"

PosicionMovil::PosicionMovil(int coordenadaX, int coordenadaY, int minimoY, int minimoX, int maximoX) : Posicion() {
    this->posicionX= (float)coordenadaX;
    this->posicionY= coordenadaY;
    this->minimoY = minimoY;
    this->minimoX = minimoX;
    this->maximoX = maximoX;
}

PosicionMovil::PosicionMovil(int coordenadaX, int coordenadaY) : Posicion() {
    this->posicionX= (float)coordenadaX;
    this->posicionY= coordenadaY;
    this->minimoY = 2147483647;
    this->minimoX = -2147483648;
    this->maximoX = 2147483647;
}

void PosicionMovil::moverHorizontal(float cantidadAMover) {
    if(((posicionX + cantidadAMover) <= (float)maximoX) && ((posicionX + cantidadAMover) >= (float)minimoX))
        this->posicionX+=cantidadAMover;
}

void PosicionMovil::moverVertical(int cantidadAMover) {
    if(posicionY + cantidadAMover < minimoY){
        posicionY = minimoY;
    }else{
        this->posicionY+=cantidadAMover;
    }
}

void PosicionMovil::actualizarLimiteTerrenoIzq(int limite) {
    minimoX = limite;
}

void PosicionMovil::actualizarLimiteTerrenoDer(int limite) {
    maximoX = limite;
}
