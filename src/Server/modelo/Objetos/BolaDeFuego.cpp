#include "BolaDeFuego.hpp"

BolaDeFuego::BolaDeFuego(PosicionFija posicionInicial, int direccion, float velocidadDeInercia) {
    posicion = new PosicionMovil(posicionInicial.obtenerPosX(), posicionInicial.obtenerPosY());
    sprite = new SpriteBolaDeFuego();
    velocidadX = direccion==DERECHA?VELOCIDAD_X_INICIAL:-VELOCIDAD_X_INICIAL;
    velocidadX += velocidadDeInercia;
    velocidadY = VELOCIDAD_Y_INICIAL;
}

bool BolaDeFuego::debeDesaparecer() {
    // Cuando pasen x segundos o **>> choque contra algo <<** (tubería, bloque, enemigo, piso...)debería desaparecer ... diría.
    return posicion->obtenerPosY() <= 0; //todo: sumarle la altura de la bola de fuego. Que son 15 píxeles, pero ese número está del lado del cliente T.T
}

void BolaDeFuego::actualizar() {
    posicion->moverHorizontal(velocidadX);
    posicion->moverVertical(velocidadY);
    sprite->actualizarSprite();
    velocidadY += EFECTO_GRAVITACIONAL;
}

BolaDeFuego::~BolaDeFuego() {
    delete posicion;
    delete sprite;
}

efecto_t BolaDeFuego::serializar() {
    auto posX = (unsigned short ) posicion->obtenerPosX();
    auto posY = (unsigned short ) posicion->obtenerPosY();
    return {posX, posY, static_cast<uint8_t>(sprite->obtenerEstadoActual()), BOLA_DE_FUEGO};
}

int BolaDeFuego::obtenerPosicionX() {
    return posicion->obtenerPosX();
}
