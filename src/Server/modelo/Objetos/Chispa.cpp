#include "Chispa.hpp"

Chispa::Chispa(Posicion posicionInicial) {
    int desfaseX = 20;
    posicion = new PosicionFija(posicionInicial.obtenerPosX()+desfaseX, posicionInicial.obtenerPosY());
    sprite = new SpriteChispa();

}

bool Chispa::debeDesaparecer() {
    return ciclos >= CICLOS_PARA_DESAPARECER;
}

Chispa::~Chispa() = default;

void Chispa::actualizar() {
    ciclos++;
    sprite->actualizarSprite();
}

efecto_t Chispa::serializar() {
    auto posX = (unsigned short ) posicion->obtenerPosX();
    auto posY = (unsigned short ) posicion->obtenerPosY();
    return {posX, posY, static_cast<uint8_t>(sprite->obtenerEstadoActual()), CHISPA};
}

int Chispa::obtenerPosicionX() {
    return posicion->obtenerPosX();
}

