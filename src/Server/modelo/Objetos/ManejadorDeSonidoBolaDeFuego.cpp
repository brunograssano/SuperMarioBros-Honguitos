#include <src/Server/Botonera/Botonera.hpp>
#include "ManejadorDeSonidoBolaDeFuego.hpp"
#include "src/Utils/Constantes.hpp"

ManejadorDeSonidoBolaDeFuego::ManejadorDeSonidoBolaDeFuego(int idMario) {
    this->id = idMario;
    mapaSonidoColisionPorIzquierda[COLISION_ID_KOOPA] = "PisaKoopa";
    mapaSonidoColisionPorDerecha[COLISION_ID_KOOPA] = "PisaKoopa";
    mapaSonidoColisionPorArriba[COLISION_ID_KOOPA] = "PisaKoopa";
    mapaSonidoColisionPorAbajo[COLISION_ID_KOOPA] = "PisaKoopa";

    mapaSonidoColisionPorIzquierda[COLISION_ID_GOOMBA] = "MataGoomba";
    mapaSonidoColisionPorDerecha[COLISION_ID_GOOMBA] = "MataGoomba";
    mapaSonidoColisionPorArriba[COLISION_ID_GOOMBA] = "MataGoomba";
    mapaSonidoColisionPorAbajo[COLISION_ID_GOOMBA] = "MataGoomba";
}