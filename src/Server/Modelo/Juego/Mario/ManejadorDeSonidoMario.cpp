#include "src/Server/Botonera/Botonera.hpp"
#include "ManejadorDeSonidoMario.hpp"
#include "src/Utils/Constantes.hpp"

ManejadorDeSonidoMario::ManejadorDeSonidoMario(int idMario) {
    this->id = idMario;
    mapaSonidoColisionPorAbajo[COLISION_ID_FLOR] = SONIDO_AGARRA_POWERUP;
    mapaSonidoColisionPorArriba[COLISION_ID_FLOR] = SONIDO_AGARRA_POWERUP;
    mapaSonidoColisionPorDerecha[COLISION_ID_FLOR] = SONIDO_AGARRA_POWERUP;
    mapaSonidoColisionPorIzquierda[COLISION_ID_FLOR] = SONIDO_AGARRA_POWERUP;

    mapaSonidoColisionPorAbajo[COLISION_ID_MONEDA] = SONIDO_AGARRAR_MONEDA;
    mapaSonidoColisionPorArriba[COLISION_ID_MONEDA] = SONIDO_AGARRAR_MONEDA;
    mapaSonidoColisionPorDerecha[COLISION_ID_MONEDA] = SONIDO_AGARRAR_MONEDA;
    mapaSonidoColisionPorIzquierda[COLISION_ID_MONEDA] = SONIDO_AGARRAR_MONEDA;

    mapaSonidoColisionPorAbajo[COLISION_ID_GOOMBA] = SONIDO_MATAR_GOOMBA;
    mapaSonidoColisionPorAbajo[COLISION_ID_KOOPA] = SONIDO_MATAR_KOOPA;
}

void ManejadorDeSonidoMario::activarSonidoFlor() {
    mapaSonidoColisionPorAbajo[COLISION_ID_FLOR] = SONIDO_AGARRA_POWERUP;
    mapaSonidoColisionPorArriba[COLISION_ID_FLOR] = SONIDO_AGARRA_POWERUP;
    mapaSonidoColisionPorDerecha[COLISION_ID_FLOR] = SONIDO_AGARRA_POWERUP;
    mapaSonidoColisionPorIzquierda[COLISION_ID_FLOR] = SONIDO_AGARRA_POWERUP;
}

void ManejadorDeSonidoMario::desactivarSonidoFlor() {
    mapaSonidoColisionPorAbajo.erase(COLISION_ID_FLOR);
    mapaSonidoColisionPorArriba.erase(COLISION_ID_FLOR);
    mapaSonidoColisionPorDerecha.erase(COLISION_ID_FLOR);
    mapaSonidoColisionPorIzquierda.erase(COLISION_ID_FLOR);
}

void ManejadorDeSonidoMario::reproducirSonidoMuerte() {
    Botonera::getInstance()->agregarSonido(SONIDO_MORIR, id);
}

void ManejadorDeSonidoMario::reproducirSonidoDisparo(int tipo){
    if(tipo == BOLA_DE_FUEGO){
        Botonera::getInstance()->agregarSonido(SONIDO_LANZAR_BOLA_DE_FUEGO, id);
    }else if(tipo == CHISPA){
        Botonera::getInstance()->agregarSonido(SONIDO_LANZAR_CHISPA, id);
    }
}

void ManejadorDeSonidoMario::reproducirSonidoSalto(){
    Botonera::getInstance()->agregarSonido(SONIDO_SALTO, id);
}

void ManejadorDeSonidoMario::reproducirSonidoMoneda() {
    Botonera::getInstance()->agregarSonido(SONIDO_AGARRAR_MONEDA, id);
}
