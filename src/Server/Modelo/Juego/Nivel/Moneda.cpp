#include "Moneda.hpp"
#include "src/Server/Modelo/Juego/Posiciones/PosicionFija.hpp"


Moneda::Moneda(int coordenadaX, int coordenadaY) {
    this->posicion = PosicionFija((coordenadaX/40)*40, (coordenadaY/40)*40);
    this->sprite = SpriteMoneda();
    agarrada = false;
    Moneda::inicializarMapasDeColision();
}

void Moneda::actualizar() {
    this->sprite.actualizarSprite();
}

entidad_t Moneda::serializar() {
    entidad_t monedaSerializada = {0,0,0,0,0,false};
    monedaSerializada.x = posicion.obtenerPosX();
    monedaSerializada.y = posicion.obtenerPosY();
    monedaSerializada.recorteX = sprite.obtenerEstadoActual();
    return monedaSerializada;
}

int Moneda::obtenerPosicionX() {
    return this->posicion.obtenerPosX();
}

int Moneda::obtenerPosicionY() {
    return this->posicion.obtenerPosY();
}

std::string Moneda::obtenerColisionID() {
    return COLISION_ID_MONEDA;
}

rectangulo_t Moneda::obtenerRectangulo() {
    int x = posicion.obtenerPosX();
    int y = posicion.obtenerPosY();
    int w = LARGO_MONEDA;
    int h = LARGO_MONEDA;
    return {x, x+w, y, y+h, h, w};
}

void Moneda::inicializarMapasDeColision() {
    auto pAgarrar = (void (Colisionable::*)(void*))&Moneda::agarrar;
    Colisionable::parFuncionColisionContexto_t parAgarrarMoneda = {pAgarrar, nullptr};

    mapaColisionesPorDerecha[COLISION_ID_MARIO] = parAgarrarMoneda;
    mapaColisionesPorIzquierda[COLISION_ID_MARIO] = parAgarrarMoneda;
    mapaColisionesPorArriba[COLISION_ID_MARIO] = parAgarrarMoneda;
    mapaColisionesPorAbajo[COLISION_ID_MARIO] = parAgarrarMoneda;
}

bool Moneda::fueAgarrada() const {
    return agarrada;
}

void Moneda::agarrar(void *ptr) {
    agarrada = true;
}

bool Moneda::debeColisionar() {
    return !agarrada;
}

void Moneda::elevar(int y) {
    int yAnt = posicion.obtenerPosY();
    int xAnt = posicion.obtenerPosX();
    posicion = PosicionFija(xAnt, yAnt + y);
}
