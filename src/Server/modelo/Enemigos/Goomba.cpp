#include "Goomba.hpp"
#include "../../sprites/SpriteGoomba.hpp"

#define PUNTOS_GOOMBA 500

Goomba::Goomba(int tipoColor) {
    spriteEnemigo = new SpriteGoomba(tipoColor);
    this->tipoColor = tipoColor;
    velocidadX = obtenerVelocidad();
    puntos = PUNTOS_GOOMBA;
}

enemigo_t Goomba::serializar() {
    return serializarEnemigo(TIPO_GOOMBA);
}

Goomba::~Goomba() {
    delete posicionActual;
    delete spriteEnemigo;
}
