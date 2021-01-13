#include "RecorteChispa.hpp"
#include "src/Utils/Constantes.hpp"

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
    return estadosPosibles[recorte<CANTIDAD_DE_RECORTES?recorte:recorte-CANTIDAD_DE_RECORTES];
}

int RecorteChispa::obtenerAltura() {
    return ALTO_CHISPA;
}

int RecorteChispa::obtenerAnchura() {
    return ANCHO_CHISPA;
}

int RecorteChispa::direccion(int recorte){
    return recorte<CANTIDAD_DE_RECORTES?DERECHA:IZQUIERDA;
}