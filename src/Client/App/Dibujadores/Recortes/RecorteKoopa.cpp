#include "RecorteKoopa.hpp"

#define ANCHO_KOOPA 16
#define ALTO_KOOPA 24

RecorteKoopa::RecorteKoopa() {
    inicializarEstados(ESTADOS_KOOPA,ANCHO_KOOPA,ALTO_KOOPA,ANCHO_KOOPA);
}

int RecorteKoopa::obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) {
    return ANCHO_ENEMIGOS;
}

int RecorteKoopa::obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) {
    return ALTO_ENEMIGOS;
}

