#include "Ladrillo.hpp"

Ladrillo::Ladrillo(int coordenadaX, int coordenadaY, int tipo) {
    int coordenadaXNormalizada = normalizarCoordenadaIngresada(coordenadaX);
    int coordenadaYNormalizada = normalizarCoordenadaIngresada(coordenadaY);

    posicion = new PosicionFija(coordenadaXNormalizada, coordenadaYNormalizada);
    tipoBloque = tipo;
    spriteBloque = new SpriteLadrillo(tipo);
}

Ladrillo::~Ladrillo() {
    delete posicion;
    delete spriteBloque;
}
