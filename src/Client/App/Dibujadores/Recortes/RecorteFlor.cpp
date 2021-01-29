#include "RecorteFlor.hpp"

#define CANTIDAD_POZOS 4
#define ANCHO_FONDO_POZO_SPRITE 16
#define ALTO_FONDO_POZO_SPRITE 16
#define DESPLAZAMIENTO_FLOR 16

RecorteFlor::RecorteFlor() {
    inicializarEstados(CANTIDAD_POZOS, DESPLAZAMIENTO_FLOR, ALTO_FONDO_POZO_SPRITE, ANCHO_FONDO_POZO_SPRITE);
}

int RecorteFlor::obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) {
    return ANCHO_FLOR;
}

int RecorteFlor::obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) {
    return ALTO_FLOR;
}
