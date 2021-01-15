#include "Ladrillo.hpp"

Ladrillo::Ladrillo(int coordenadaX, int coordenadaY, int tipo) {
    int coordenadaXNormalizada = normalizarCoordenadaIngresada(coordenadaX);
    int coordenadaYNormalizada = normalizarCoordenadaIngresada(coordenadaY);

    posicion = PosicionFija(coordenadaXNormalizada, coordenadaYNormalizada);
    tipoBloque = tipo;
    spriteBloque = new SpriteLadrillo();
    Ladrillo::inicializarMapasDeColision();
}


void Ladrillo::romperse(void *ptr) {
    spriteBloque->usarse();
}

void Ladrillo::inicializarMapasDeColision() {
    auto pRomperse = (void (Colisionable::*)(void*)) &Ladrillo::romperse;

    Colisionable::parFuncionColisionContexto_t parRomperse = {pRomperse, nullptr};
    mapaColisionesPorAbajo[COLISION_ID_MARIO] = parRomperse;
}

string Ladrillo::obtenerColisionID() {
    return COLISION_ID_LADRILLO;
}

Ladrillo::~Ladrillo() {
    delete spriteBloque;
}

