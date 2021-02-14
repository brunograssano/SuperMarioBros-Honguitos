#include "RecorteGoomba.hpp"
#define CORRIMIENTO_X 16
#define ALTO_GOOMBA 16
#define ANCHO_GOOMBA 16

RecorteGoomba::RecorteGoomba() {
    inicializarEstados(ESTADOS_GOOMBA,CORRIMIENTO_X,ALTO_GOOMBA,ANCHO_GOOMBA);
}

int RecorteGoomba::obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) {
    return ANCHO_ENEMIGOS;
}

int RecorteGoomba::obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) {
    return ALTO_ENEMIGOS;
}
