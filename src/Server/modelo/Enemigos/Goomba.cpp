#include "Goomba.hpp"
#include "../../sprites/SpriteGoomba.hpp"
#include "src/Utils/Constantes.hpp"

Goomba::Goomba(int tipoColor) {
    spriteEnemigo = new SpriteGoomba(tipoColor);
    this->tipoColor = tipoColor;
    velocidadX = obtenerVelocidad();
    loMataron = false;
    inicializarMapasDeColision();
    posicionActual = new PosicionMovil(0, 0);
}

enemigo_t Goomba::serializar() {
    return serializarEnemigo(TIPO_GOOMBA);
}

Goomba::~Goomba() {
    delete posicionActual;
    delete spriteEnemigo;
}

string Goomba::obtenerColisionID() {
    return COLISION_ID_GOOMBA;
}