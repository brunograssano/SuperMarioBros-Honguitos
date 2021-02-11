#include "RecorteBloque.hpp"

const int DESPLAZAMIENTO_BLOQUES_X = 16;
const int ALTO_BLOQUE = 16;
const int ANCHO_BLOQUE = ALTO_BLOQUE;

RecorteBloque::RecorteBloque() {
    inicializarEstados(ESTADOS_BLOQUE,DESPLAZAMIENTO_BLOQUES_X,ALTO_BLOQUE,ANCHO_BLOQUE);
}

int RecorteBloque::obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) {
    return LARGO_BLOQUE;
}

int RecorteBloque::obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) {
    return LARGO_BLOQUE;
}
