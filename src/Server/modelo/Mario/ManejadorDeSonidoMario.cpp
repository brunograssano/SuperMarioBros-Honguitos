#include <src/Server/Botonera/Botonera.hpp>
#include "ManejadorDeSonidoMario.hpp"
#include "src/Utils/Constantes.hpp"

ManejadorDeSonidoMario::ManejadorDeSonidoMario(int idMario) {
    this->id = idMario;
    mapaSonidoColisionPorAbajo[COLISION_ID_FLOR] = "AgarraHongo";
    mapaSonidoColisionPorArriba[COLISION_ID_FLOR] = "AgarraHongo";
    mapaSonidoColisionPorDerecha[COLISION_ID_FLOR] = "AgarraHongo";
    mapaSonidoColisionPorIzquierda[COLISION_ID_FLOR] = "AgarraHongo";

    mapaSonidoColisionPorAbajo[COLISION_ID_MONEDA] = "AgarrarMoneda";
    mapaSonidoColisionPorArriba[COLISION_ID_MONEDA] = "AgarrarMoneda";
    mapaSonidoColisionPorDerecha[COLISION_ID_MONEDA] = "AgarrarMoneda";
    mapaSonidoColisionPorIzquierda[COLISION_ID_MONEDA] = "AgarrarMoneda";

    mapaSonidoColisionPorAbajo[COLISION_ID_GOOMBA] = "MataGoomba";
    mapaSonidoColisionPorAbajo[COLISION_ID_KOOPA] = "PisaKoopa";

}

void ManejadorDeSonidoMario::activarSonidoFlor() {
    mapaSonidoColisionPorAbajo[COLISION_ID_FLOR] = "AgarraHongo";
    mapaSonidoColisionPorArriba[COLISION_ID_FLOR] = "AgarraHongo";
    mapaSonidoColisionPorDerecha[COLISION_ID_FLOR] = "AgarraHongo";
    mapaSonidoColisionPorIzquierda[COLISION_ID_FLOR] = "AgarraHongo";
}

void ManejadorDeSonidoMario::desactivarSonidoFlor() {
    mapaSonidoColisionPorAbajo.erase(COLISION_ID_FLOR);
    mapaSonidoColisionPorArriba.erase(COLISION_ID_FLOR);
    mapaSonidoColisionPorDerecha.erase(COLISION_ID_FLOR);
    mapaSonidoColisionPorIzquierda.erase(COLISION_ID_FLOR);
}

void ManejadorDeSonidoMario::reproducirSonidoMuerte() {
    Botonera::getInstance()->agregarSonido("MarioMorir", id);
}

void ManejadorDeSonidoMario::reproducirSonidoDisparo(int tipo){
    if(tipo == BOLA_DE_FUEGO){
        Botonera::getInstance()->agregarSonido("LanzaFuego", id);
    }
}

void ManejadorDeSonidoMario::reproducirSonidoSalto(){
    Botonera::getInstance()->agregarSonido("EfectoSalto", id);
}

void ManejadorDeSonidoMario::reproducirSonidoMoneda() {
    Botonera::getInstance()->agregarSonido("AgarrarMoneda", id);
}
