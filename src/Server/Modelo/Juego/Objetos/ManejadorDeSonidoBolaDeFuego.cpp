#include "src/Server/Botonera/Botonera.hpp"
#include "ManejadorDeSonidoBolaDeFuego.hpp"
#include "src/Utils/Constantes.hpp"

ManejadorDeSonidoBolaDeFuego::ManejadorDeSonidoBolaDeFuego(int idMario) {
    this->id = idMario;
    mapaSonidoColisionPorIzquierda[COLISION_ID_KOOPA] = SONIDO_MATAR_KOOPA;
    mapaSonidoColisionPorDerecha[COLISION_ID_KOOPA] = SONIDO_MATAR_KOOPA;
    mapaSonidoColisionPorArriba[COLISION_ID_KOOPA] = SONIDO_MATAR_KOOPA;
    mapaSonidoColisionPorAbajo[COLISION_ID_KOOPA] = SONIDO_MATAR_KOOPA;

    mapaSonidoColisionPorIzquierda[COLISION_ID_GOOMBA] = SONIDO_MATAR_GOOMBA;
    mapaSonidoColisionPorDerecha[COLISION_ID_GOOMBA] = SONIDO_MATAR_GOOMBA;
    mapaSonidoColisionPorArriba[COLISION_ID_GOOMBA] = SONIDO_MATAR_GOOMBA;
    mapaSonidoColisionPorAbajo[COLISION_ID_GOOMBA] = SONIDO_MATAR_GOOMBA;
}

void ManejadorDeSonidoBolaDeFuego::reproducirExplosion() {
    Botonera::getInstance()->agregarSonido(SONIDO_EXPLOSION_BOLA_DE_FUEGO, id);
}

void ManejadorDeSonidoBolaDeFuego::reproducirRebote() {
    Botonera::getInstance()->agregarSonido(SONIDO_REBOTE_BOLA_DE_FUEGO, id);
}
