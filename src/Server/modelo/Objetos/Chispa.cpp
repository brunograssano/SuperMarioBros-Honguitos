#include "Chispa.hpp"

Chispa::Chispa(Posicion posicionInicial) {
    posicion = new PosicionFija(posicionInicial.obtenerPosX(), posicionInicial.obtenerPosY());
    sprite = new SpriteChispa();

}

bool Chispa::debeDesaparecer() {
    return true;
}

Chispa::~Chispa() = default;

void Chispa::actualizar() {}

efecto_t Chispa::serializar() {
    auto posX = (unsigned short ) posicion->obtenerPosX();
    auto posY = (unsigned short ) posicion->obtenerPosY();
    return {posX, posY, CHISPA};
}

int Chispa::obtenerPosicionX() {
    return posicion->obtenerPosX();
}

