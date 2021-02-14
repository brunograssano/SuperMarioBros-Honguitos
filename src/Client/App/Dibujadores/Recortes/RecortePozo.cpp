#include "RecortePozo.hpp"
#include "src/Utils/Constantes.hpp"

#define ANCHO_POZO_PIXEL_IMAGEN 180
#define ALTO_POZO_PIXEL_IMAGEN 60
#define MAX_ESTADOS_POZOS 5
const int DESPLAZAMIENTO_X = 0;

RecortePozo::RecortePozo() {
    inicializarEstados(MAX_ESTADOS_POZOS,DESPLAZAMIENTO_X,ALTO_POZO_PIXEL_IMAGEN, ANCHO_POZO_PIXEL_IMAGEN);
}

int RecortePozo::obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) {
    return ANCHO_POZO;
}

int RecortePozo::obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) {
    return ALTO_POZO;
}
