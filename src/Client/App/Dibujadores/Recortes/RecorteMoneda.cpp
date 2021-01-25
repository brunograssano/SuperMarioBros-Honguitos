#include "RecorteMoneda.hpp"
#define ALTO_MONEDA 17
#define ANCHO_MONEDA 16
#define DESPLAZAMIENTO_X 16

RecorteMoneda::RecorteMoneda() {
    inicializarEstados(ESTADOS_MONEDA,DESPLAZAMIENTO_X,ALTO_MONEDA,ANCHO_MONEDA);
}

