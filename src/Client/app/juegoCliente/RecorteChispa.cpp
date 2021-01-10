#include "RecorteChispa.hpp"

const int ALTO_IMAGEN_PIXEL = 22;
const int ANCHO_IMAGEN_PIXEL = 31;
const int PASO_PROXIMO_SPRITE = 32;

RecorteChispa::RecorteChispa() {
    int corrimientoEnImagen = 0;

    for(int i=0;i<CANTIDAD_DE_RECORTES;i++){
        estadosPosibles[i].x = corrimientoEnImagen;
        estadosPosibles[i].y = 0;
        estadosPosibles[i].w = ANCHO_IMAGEN_PIXEL;
        estadosPosibles[i].h = ALTO_IMAGEN_PIXEL;
        corrimientoEnImagen+= PASO_PROXIMO_SPRITE;
    }

}

SDL_Rect RecorteChispa::obtenerRecorte(int recorte) {
    return estadosPosibles[recorte];
}

int RecorteChispa::obtenerAltura() {
    return 44;
}

int RecorteChispa::obtenerAnchura() {
    return 64;
}
