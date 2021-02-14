#include "RecorteChispa.hpp"
#include "src/Utils/Constantes.hpp"

const int ALTO_IMAGEN_PIXEL = 22;
const int ANCHO_IMAGEN_PIXEL = 31;
const int PASO_PROXIMO_SPRITE = 32;

RecorteChispa::RecorteChispa() {
    inicializarEstados(CANTIDAD_DE_RECORTES, PASO_PROXIMO_SPRITE, ALTO_IMAGEN_PIXEL, ANCHO_IMAGEN_PIXEL);
}

int RecorteChispa::obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) {
    return ALTO_CHISPA;
}

int RecorteChispa::obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) {
    return ANCHO_CHISPA;
}
