#include "MonedaSorpresa.hpp"
#include "src/Utils/Constantes.hpp"
#include "src/Utils/Utils.hpp"

const int FUERZA = 30;

MonedaSorpresa::MonedaSorpresa(Posicion* posicionInicial) {
    _debeDesaparecer = false;
    posYInicial = posicionInicial->obtenerPosY();
    posicion = PosicionMovil(posicionInicial->obtenerPosX(), posicionInicial->obtenerPosY(),
                             posicionInicial->obtenerPosY(), posicionInicial->obtenerPosX(), posicionInicial->obtenerPosX());
    movimiento = MovimientoVertical(FUERZA);
    Terreno* tierra = new Tierra();
    movimiento.saltar(tierra);
    delete tierra;
    MonedaSorpresa::inicializarMapasDeColision();
}

void MonedaSorpresa::usarse(Mario *mario) {
    mario->agregarMoneda();
}

efecto_t MonedaSorpresa::serializar() {
    unsigned short x = posicion.obtenerPosX();
    unsigned short y = posicion.obtenerPosY();
    uint8_t recorte = sprite.obtenerEstadoActual();
    return {x, y, recorte, MONEDA_FLOTANTE};
}

void MonedaSorpresa::actualizar() {
    movimiento.mover(&posicion);
    if(posicion.obtenerPosY() == posYInicial){
        _debeDesaparecer = true;
    }
    sprite.actualizarSprite();
}

int MonedaSorpresa::obtenerPosicionX() {
    return posicion.obtenerPosX();
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