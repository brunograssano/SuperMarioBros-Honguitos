#include "Koopa.hpp"
#include "../../sprites/SpriteKoopa.hpp"
#include "src/Utils/Constantes.hpp"

Koopa::Koopa(int tipoColor) {
    spriteEnemigo = new SpriteKoopa();
    this->tipoColor = tipoColor;
    velocidadX = obtenerVelocidad();
    loMataron = false;
    this->inicializarMapasDeColision();
    posicionActual = new PosicionMovil(0, 0);
}

Koopa::~Koopa() {
    delete spriteEnemigo;
    delete posicionActual;
}

enemigo_t Koopa::serializar() {
    return serializarEnemigo(TIPO_KOOPA);
}

string Koopa::obtenerColisionID() {
    return COLISION_ID_KOOPA;
}
