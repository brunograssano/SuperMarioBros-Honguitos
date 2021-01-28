#include "Chispa.hpp"

Chispa::Chispa(const Posicion& posicionInicial, int direccion) {
    int desfaseX = direccion==DERECHA?20:-60;
    posicion = new PosicionFija(posicionInicial.obtenerPosX()+desfaseX, posicionInicial.obtenerPosY());
    sprite = new SpriteChispa(direccion);
    inicializarMapasDeColision();
}

bool Chispa::debeDesaparecer() {
    return ciclos >= CICLOS_PARA_DESAPARECER;
}

Chispa::~Chispa() = default;

void Chispa::actualizar() {
    ciclos++;
    sprite->actualizarSprite();
}

entidad_t Chispa::serializar() {
    entidad_t chispaSerializada = {0,0,0,0,0, false};
    chispaSerializada.x = posicion->obtenerPosX();
    chispaSerializada.y = posicion->obtenerPosY();
    chispaSerializada.recorteX = sprite->obtenerEstadoActual();
    chispaSerializada.tipo = CHISPA;
    return chispaSerializada;
}

int Chispa::obtenerPosicionX() {
    return posicion->obtenerPosX();
}

std::string Chispa::obtenerColisionID() {
    return COLISION_ID_CHISPA;
}

rectangulo_t Chispa::obtenerRectangulo() {
    int x = posicion->obtenerPosX();
    int y = posicion->obtenerPosY();
    int w = ANCHO_CHISPA;
    int h = ALTO_CHISPA;
    return {x, x+w, y, y+w, h, w};
}

bool Chispa::debeColisionar() {
    return false;
}

void Chispa::inicializarMapasDeColision() {}

int Chispa::tipoDeEfecto() {
    return CHISPA;
}
