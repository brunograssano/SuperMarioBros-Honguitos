#include "src/Server/Botonera/Botonera.hpp"
#include "ManejadorDeSonido.hpp"

void ManejadorDeSonido::reproducirSonidoIzquierda(const std::string& id_colision) {
    agregarSonido(mapaSonidoColisionPorIzquierda, id_colision);
}

void ManejadorDeSonido::reproducirSonidoDerecha(const std::string& id_colision) {
    agregarSonido(mapaSonidoColisionPorDerecha, id_colision);
}

void ManejadorDeSonido::reproducirSonidoArriba(const std::string& id_colision) {
    agregarSonido(mapaSonidoColisionPorArriba, id_colision);
}

void ManejadorDeSonido::reproducirSonidoAbajo(const std::string& id_colision) {
    agregarSonido(mapaSonidoColisionPorAbajo, id_colision);
}

void ManejadorDeSonido::agregarSonido(std::map<std::string, uint8_t> mapaSonido, const std::string& id_colision) const {
    Botonera::getInstance()->agregarSonido(mapaSonido[id_colision], id);
}
