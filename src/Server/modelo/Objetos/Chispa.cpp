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

efecto_t Chispa::serializar() {
    auto posX = (unsigned short ) posicion->obtenerPosX();
    auto posY = (unsigned short ) posicion->obtenerPosY();
    return {posX, posY, static_cast<uint8_t>(sprite->obtenerEstadoActual()), CHISPA};
}

int Chispa::obtenerPosicionX() {
    return posicion->obtenerPosX();
}

string Chispa::obtenerColisionID() {
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