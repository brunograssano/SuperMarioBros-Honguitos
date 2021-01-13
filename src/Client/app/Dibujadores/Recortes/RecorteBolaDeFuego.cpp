#include "RecorteBolaDeFuego.hpp"
const int ALTO_IMAGEN_PIXEL = 32;
const int ANCHO_IMAGEN_PIXEL = 31;
const int PASO_PROXIMO_SPRITE = 32;
const int CANTIDAD_DE_RECORTES = 7;

RecorteBolaDeFuego::RecorteBolaDeFuego() {
    inicializarEstados(CANTIDAD_DE_RECORTES,PASO_PROXIMO_SPRITE,ALTO_IMAGEN_PIXEL,ANCHO_IMAGEN_PIXEL);
}

int RecorteBolaDeFuego::obtenerAnchuraParaDibujarImagen() {
    return ANCHO_BOLA;
}

int RecorteBolaDeFuego::obtenerAlturaParaDibujarImagen() {
    return ALTO_BOLA;
}
