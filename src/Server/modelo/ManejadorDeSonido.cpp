#include "src/Server/Botonera/Botonera.hpp"
#include "ManejadorDeSonido.hpp"

void ManejadorDeSonido::reproducirSonidoIzquierda(std::string id_colision) {
    agregarSonido(mapaSonidoColisionPorIzquierda, id_colision);
}

void ManejadorDeSonido::reproducirSonidoDerecha(std::string id_colision) {
    agregarSonido(mapaSonidoColisionPorDerecha, id_colision);
}

void ManejadorDeSonido::reproducirSonidoArriba(std::string id_colision) {
    agregarSonido(mapaSonidoColisionPorArriba, id_colision);
}

void ManejadorDeSonido::reproducirSonidoAbajo(std::string id_colision) {
    agregarSonido(mapaSonidoColisionPorAbajo, id_colision);
}

void ManejadorDeSonido::agregarSonido(std::map<std::string, std::string> mapaSonido, std::string id_colision) {
    Botonera::getInstance()->agregarSonido(mapaSonido[id_colision], id);
}
