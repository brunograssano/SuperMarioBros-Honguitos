#include "Goomba.hpp"
#include "../../sprites/SpriteGoomba.hpp"
#include "src/Utils/Constantes.hpp"
#define DEFAULT 100

Goomba::Goomba(int tipoColor){
    spriteEnemigo = new SpriteGoomba();
    this->tipoColor = tipoColor;
    loMataron = false;
    Enemigo::inicializarMapasDeColision();
    posicionActual = PosicionMovil(DEFAULT, DEFAULT);
}

enemigo_t Goomba::serializar() {
    return serializarEnemigo(TIPO_GOOMBA);
}

Goomba::~Goomba() {
    delete spriteEnemigo;
}

string Goomba::obtenerColisionID() {
    return COLISION_ID_GOOMBA;
}