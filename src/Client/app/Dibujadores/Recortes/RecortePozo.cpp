#include "RecortePozo.hpp"

#define ALTO_POZO 60
#define ANCHO_POZO 180
#define MAX_TIPOS 3
const int DESPLAZAMIENTO_X = 0;

RecortePozo::RecortePozo() {
    inicializarEstados(MAX_TIPOS,DESPLAZAMIENTO_X,ALTO_POZO,ANCHO_POZO);
}
