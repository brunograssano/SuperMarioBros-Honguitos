#include "MonedaSorpresa.hpp"
#include "src/Utils/Constantes.hpp"
#include "src/Utils/Utils.hpp"

MonedaSorpresa::MonedaSorpresa(Posicion* posicionInicial) {
    _debeDesaparecer = true; //todo: false [Movimiento vertical feat]
    posicion = PosicionMovil(posicionInicial->obtenerPosX(), posicionInicial->obtenerPosY(),
                             posicionInicial->obtenerPosY(), posicionInicial->obtenerPosX(), posicionInicial->obtenerPosX());
    inicializarMapasDeColision();
    //todo: sprite feat.
    //todo: movimiento vertical feat.
}

void MonedaSorpresa::usarse(Mario *mario) {
    mario->agregarMoneda();
}

efecto_t MonedaSorpresa::serializar() {
    unsigned short x = posicion.obtenerPosX();
    unsigned short y = posicion.obtenerPosY();
    return {x, y, 0/*todo: sprite*/, MONEDA_FLOTANTE};
}

void MonedaSorpresa::actualizar() {
    //todo: movimiento vertical feat.
    //todo: sprite feat.
}

int MonedaSorpresa::obtenerPosicionX() {
    return posicion.obtenerPosX();;
}

string MonedaSorpresa::obtenerColisionID() {
    return COLISION_ID_MONEDA_FLOTANTE;
}

rectangulo_t MonedaSorpresa::obtenerRectangulo() {
    int x = posicion.obtenerPosX();
    int y = posicion.obtenerPosY();
    int w = ANCHO_FLOR;
    int h = ALTO_FLOR;
    return {x, x+w, y, y+h, h, w};
}

bool MonedaSorpresa::debeColisionar() {
    return !_debeDesaparecer;
}

void MonedaSorpresa::inicializarMapasDeColision() {}