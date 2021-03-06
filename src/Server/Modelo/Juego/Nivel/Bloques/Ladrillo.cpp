#include "Ladrillo.hpp"

#include "src/Server/Modelo/Juego/Sprites/SpriteLadrillo.hpp"

Ladrillo::Ladrillo(int coordenadaX, int coordenadaY, int tipo) {
    int coordenadaXNormalizada = normalizarCoordenadaIngresada(coordenadaX);
    int coordenadaYNormalizada = normalizarCoordenadaIngresada(coordenadaY);

    posicion = PosicionFija(coordenadaXNormalizada, coordenadaYNormalizada);
    tipoBloque = tipo;
    spriteBloque = new SpriteLadrillo();
    Ladrillo::inicializarMapasDeColision();
}


void Ladrillo::romperse(__attribute__((unused))void *ptr) {
    spriteBloque->usarse();
}

void Ladrillo::inicializarMapasDeColision() {
    auto pRomperse = (void (Colisionable::*)(void*)) &Ladrillo::romperse;

    Colisionable::parFuncionColisionContexto_t parRomperse = {pRomperse, nullptr};
    mapaColisionesPorAbajo[COLISION_ID_MARIO] = parRomperse;
}

std::string Ladrillo::obtenerColisionID() {
    return COLISION_ID_LADRILLO;
}

Ladrillo::~Ladrillo() {
    delete spriteBloque;
}

