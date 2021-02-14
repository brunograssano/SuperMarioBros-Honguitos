#include "RecorteFondoPozo.hpp"
#include "src/Utils/Constantes.hpp"

#define CANTIDAD_POZOS 5
#define ANCHO_FONDO_POZO_SPRITE 180
#define ALTO_FONDO_POZO_SPRITE 60

RecorteFondoPozo::RecorteFondoPozo() {
    inicializarEstados(CANTIDAD_POZOS, ANCHO_FONDO_POZO_SPRITE, ALTO_FONDO_POZO_SPRITE, ANCHO_FONDO_POZO_SPRITE);
}

int RecorteFondoPozo::obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) {
    return ANCHO_POZO;
}

int RecorteFondoPozo::obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) {
    return ALTO_POZO;
}
