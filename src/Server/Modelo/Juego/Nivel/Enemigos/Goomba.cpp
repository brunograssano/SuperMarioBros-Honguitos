#include "Goomba.hpp"
#include "src/Server/Modelo/Juego/Sprites/SpriteGoomba.hpp"
#include "src/Utils/Constantes.hpp"
#define DEFAULT 100

Goomba::Goomba(int tipoColor){
    spriteEnemigo = new SpriteGoomba();
    this->tipoColor = tipoColor;
    loMataron = false;
    Enemigo::inicializarMapasDeColision();
    posicionActual = PosicionMovil(DEFAULT, DEFAULT);
}

entidad_t Goomba::serializar() {
    return serializarEnemigo(TIPO_GOOMBA);
}

Goomba::~Goomba() {
    delete spriteEnemigo;
}

std::string Goomba::obtenerColisionID() {
    return COLISION_ID_GOOMBA;
}