#include "Koopa.hpp"

Koopa::Koopa(int tipoColor) {
    spriteEnemigo = new SpriteKoopa(tipoColor);
    this->tipoColor = tipoColor;
    velocidadX = obtenerVelocidad();
}

Koopa::~Koopa() {
    delete spriteEnemigo;
    delete posicionActual;
}

enemigo_t Koopa::serializar() {
    enemigo_t enemigoSerializado;
    enemigoSerializado.posX = this->obtenerPosicionX();
    enemigoSerializado.numeroRecorteX = spriteEnemigo->obtenerEstadoActual();
    enemigoSerializado.numeroRecorteY = tipoColor;
    enemigoSerializado.tipoEnemigo = TIPO_KOOPA;
    enemigoSerializado.espejar = velocidadX > 0;
    return enemigoSerializado;
}

