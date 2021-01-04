#include "Goomba.hpp"

Goomba::Goomba(int tipoColor) {
    spriteEnemigo = new SpriteGoomba(tipoColor);
    this->tipoColor = tipoColor;
    velocidadX = obtenerVelocidad();
}

enemigo_t Goomba::serializar() {
    enemigo_t enemigoSerializado;
    enemigoSerializado.posX = this->obtenerPosicionX();
    enemigoSerializado.numeroRecorteX = spriteEnemigo->obtenerEstadoActual();
    enemigoSerializado.numeroRecorteY = tipoColor;
    enemigoSerializado.tipoEnemigo = TIPO_GOOMBA;
    enemigoSerializado.espejar = false;
    return enemigoSerializado;
}

Goomba::~Goomba() {
    delete posicionActual;
    delete spriteEnemigo;
}
