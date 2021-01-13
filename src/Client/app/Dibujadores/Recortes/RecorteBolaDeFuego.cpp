#include "RecorteBolaDeFuego.hpp"
#include "src/Utils/Constantes.hpp"
const int ALTO_IMAGEN_PIXEL = 32;
const int ANCHO_IMAGEN_PIXEL = 31;
const int PASO_PROXIMO_SPRITE = 32;


RecorteBolaDeFuego::RecorteBolaDeFuego() {
    int corrimientoEnImagen = 0;

    for(auto & estadosPosible : estadosPosibles){
        estadosPosible.x = corrimientoEnImagen;
        estadosPosible.y = 0;
        estadosPosible.w = ANCHO_IMAGEN_PIXEL;
        estadosPosible.h = ALTO_IMAGEN_PIXEL;
        corrimientoEnImagen += PASO_PROXIMO_SPRITE;
    }
}

SDL_Rect RecorteBolaDeFuego::obtenerRecorte(int recorte) {
    return estadosPosibles[recorte];
}

int RecorteBolaDeFuego::obtenerAltura() {
    return ALTO_BOLA;
}

int RecorteBolaDeFuego::obtenerAnchura() {
    return ANCHO_BOLA;
}
