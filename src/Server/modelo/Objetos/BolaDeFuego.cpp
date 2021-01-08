#include "BolaDeFuego.hpp"

BolaDeFuego::BolaDeFuego(Posicion posicionInicial) {
    posicion = new PosicionMovil(posicionInicial.obtenerPosX(), posicionInicial.obtenerPosY());
    sprite = new SpriteBolaDeFuego();
}

bool BolaDeFuego::debeDesaparecer() {
    // Cuando pasen x segundos o **>> choque contra algo <<** (tubería, bloque, enemigo, piso...)debería desaparecer ... diría.
    return posicion->obtenerPosY() <= 0;
}

void BolaDeFuego::actualizar() {
    //todo: calibrar
    posicion->moverHorizontal(0.5);
    //posicion->moverVertical(-1);
}

BolaDeFuego::~BolaDeFuego() {
    delete posicion;
    delete sprite;
}

efecto_t BolaDeFuego::serializar() {
    auto posX = (unsigned short ) posicion->obtenerPosX();
    auto posY = (unsigned short ) posicion->obtenerPosY();
    return {posX, posY, BOLA_DE_FUEGO};
}

int BolaDeFuego::obtenerPosicionX() {
    return posicion->obtenerPosX();
}
