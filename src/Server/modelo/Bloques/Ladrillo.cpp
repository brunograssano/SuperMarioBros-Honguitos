#include "Ladrillo.hpp"

Ladrillo::Ladrillo(int coordenadaX, int coordenadaY, int tipo) {
    int coordenadaXNormalizada = normalizarCoordenadaIngresada(coordenadaX);
    int coordenadaYNormalizada = normalizarCoordenadaIngresada(coordenadaY);

    posicion = new PosicionFija(coordenadaXNormalizada, coordenadaYNormalizada);
    tipoLadrillo = tipo;
    spriteBloque = new SpriteLadrillo(tipo);
}

bloque_t Ladrillo::serializar() {
    bloque_t bloqueSerializado = {0, 0, 0, 0};
    bloqueSerializado.posX = posicion->obtenerPosX();
    bloqueSerializado.posY = posicion->obtenerPosY();
    bloqueSerializado.numeroRecorteX = spriteBloque->obtenerEstadoActual();
    bloqueSerializado.numeroRecorteY = tipoLadrillo;
    return bloqueSerializado;
}

Ladrillo::~Ladrillo() {
    delete posicion;
    delete spriteBloque;
}
