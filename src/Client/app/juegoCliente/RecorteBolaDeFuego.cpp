#include "RecorteBolaDeFuego.hpp"

const int ALTO_IMAGEN_PIXEL = 32;
const int ANCHO_IMAGEN_PIXEL = 31;
const int PASO_PROXIMO_SPRITE = 32;


RecorteBolaDeFuego::RecorteBolaDeFuego() {
    int corrimientoEnImagen = 0;

    for(int i=0;i<CANTIDAD_DE_RECORTES;i++){
        estadosPosibles[i].x = corrimientoEnImagen;
        estadosPosibles[i].y = 0;
        estadosPosibles[i].w = ANCHO_IMAGEN_PIXEL;
        estadosPosibles[i].h = ALTO_IMAGEN_PIXEL;
        corrimientoEnImagen+= PASO_PROXIMO_SPRITE;
    }

}

SDL_Rect RecorteBolaDeFuego::obtenerRecorte(int recorte) {
    return estadosPosibles[recorte];
}
