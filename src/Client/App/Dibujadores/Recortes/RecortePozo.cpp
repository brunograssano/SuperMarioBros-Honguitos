#include "RecortePozo.hpp"

#define ALTO_POZO 60
#define ANCHO_POZO 200
#define MAX_ESTADOS_POZOS 1
const int DESPLAZAMIENTO_X = 0;

RecortePozo::RecortePozo() {
    inicializarEstados(MAX_ESTADOS_POZOS,DESPLAZAMIENTO_X,ALTO_POZO,ANCHO_POZO);
}

int RecortePozo::obtenerAnchuraParaDibujarImagen(int tipo) {
    return ANCHO_POZO;
}

int RecortePozo::obtenerAlturaParaDibujarImagen(int tipo) {
    return ALTO_POZO;
}
