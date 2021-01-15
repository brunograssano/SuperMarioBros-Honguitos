#include "Koopa.hpp"
#include "../../sprites/SpriteKoopa.hpp"
#include "src/Utils/Constantes.hpp"
#define DEFAULT 100

Koopa::Koopa(int tipoColor) {
    spriteEnemigo = new SpriteKoopa();
    this->tipoColor = tipoColor;
    loMataron = false;
    this->inicializarMapasDeColision();
    posicionActual = PosicionMovil(DEFAULT, DEFAULT);
}

Koopa::~Koopa() {
    delete spriteEnemigo;
}

enemigo_t Koopa::serializar() {
    return serializarEnemigo(TIPO_KOOPA);
}

string Koopa::obtenerColisionID() {
    return COLISION_ID_KOOPA;
}
