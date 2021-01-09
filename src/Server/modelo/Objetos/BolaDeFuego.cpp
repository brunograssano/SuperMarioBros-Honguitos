#include "BolaDeFuego.hpp"

BolaDeFuego::BolaDeFuego(PosicionFija posicionInicial, int direccion, float velocidadDeInercia) {
    posicion = new PosicionMovil(posicionInicial.obtenerPosX(), posicionInicial.obtenerPosY());
    sprite = new SpriteBolaDeFuego();
    velocidadX = direccion==DERECHA?2.6:-2.6;
    velocidadX += velocidadDeInercia;
    velocidadY = 0.4;
}

bool BolaDeFuego::debeDesaparecer() {
    // Cuando pasen x segundos o **>> choque contra algo <<** (tubería, bloque, enemigo, piso...)debería desaparecer ... diría.
    return posicion->obtenerPosY() <= 0;
}

void BolaDeFuego::actualizar() {
    //todo: calibrar
    posicion->moverHorizontal(velocidadX);
    posicion->moverVertical(-velocidadY);
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
