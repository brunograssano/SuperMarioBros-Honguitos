#include "Koopa.hpp"
#include "../../sprites/SpriteKoopa.hpp"
#include "src/Utils/Constantes.hpp"
#define DEFAULT 100
#define VELOCIDAD_EXTRA_KOOPA 0.5

Koopa::Koopa(int tipoColor){
    this->tipoColor = tipoColor;
    loMataron = false;
    this->inicializarMapasDeColision();
    posicionActual = PosicionMovil(DEFAULT, DEFAULT);
    movimientoEnemigo = MovimientoEnemigo(VELOCIDAD_EXTRA_KOOPA);
    bool debeEspejarse = this->movimientoEnemigo.debeEspejarse();
    spriteEnemigo = new SpriteKoopa(debeEspejarse);
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
