#include "MonedaSorpresa.hpp"

#include "src/Server/Modelo/Juego/Terrenos/Tierra.hpp"

#include "src/Utils/Constantes.hpp"
#include "src/Utils/Utils.hpp"

const int FUERZA = 30;

MonedaSorpresa::MonedaSorpresa(Posicion* posicionInicial) :
    posicion(posicionInicial->obtenerPosX(), posicionInicial->obtenerPosY(),
             posicionInicial->obtenerPosY(), posicionInicial->obtenerPosX(), posicionInicial->obtenerPosX()),
    movimiento(FUERZA){
    _debeDesaparecer = false;
    posYInicial = posicionInicial->obtenerPosY();
    Terreno* tierra = new Tierra();
    movimiento.saltar(tierra);
    delete tierra;
    MonedaSorpresa::inicializarMapasDeColision();
}

void MonedaSorpresa::usarse(Mario *mario) {
    mario->agregarMoneda();
}

entidad_t MonedaSorpresa::serializar() {
    entidad_t monedaSorpresaSerializada = {0,0,0,0,0,false};
    monedaSorpresaSerializada.x = posicion.obtenerPosX();
    monedaSorpresaSerializada.y = posicion.obtenerPosY();
    monedaSorpresaSerializada.recorteX = sprite.obtenerEstadoActual();
    monedaSorpresaSerializada.tipo = MONEDA_FLOTANTE;
    return monedaSorpresaSerializada;
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

std::string MonedaSorpresa::obtenerColisionID() {
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

int MonedaSorpresa::tipoDeEfecto() {
    return MONEDA_FLOTANTE;
}
