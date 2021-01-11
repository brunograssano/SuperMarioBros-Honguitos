#include "Koopa.hpp"
#define PUNTOS_KOOPA 1000
#include "../../sprites/SpriteKoopa.hpp"

#include "src/Utils/Constantes.hpp"

Koopa::Koopa(int tipoColor) {
    spriteEnemigo = new SpriteKoopa(tipoColor);
    this->tipoColor = tipoColor;
    velocidadX = obtenerVelocidad();
    puntos = PUNTOS_KOOPA;
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
