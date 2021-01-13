#include "RecorteMonedaFlotante.hpp"
#include "src/Utils/Constantes.hpp"
const int ALTO_IMAGEN_PIXEL = 16;
const int ANCHO_IMAGEN_PIXEL = 16;
const int PASO_PROXIMO_SPRITE = 16;


RecorteMonedaFlotante::RecorteMonedaFlotante() {
    int corrimientoEnImagen = 0;

    for(auto & estadosPosible : estadosPosibles){
        estadosPosible.x = corrimientoEnImagen;
        estadosPosible.y = 0;
        estadosPosible.w = ANCHO_IMAGEN_PIXEL;
        estadosPosible.h = ALTO_IMAGEN_PIXEL;
        corrimientoEnImagen += PASO_PROXIMO_SPRITE;
    }
}

SDL_Rect RecorteMonedaFlotante::obtenerRecorte(int recorte) {
    return estadosPosibles[recorte];
}

int RecorteMonedaFlotante::obtenerAltura() {
    return LARGO_MONEDA;
}

int RecorteMonedaFlotante::obtenerAnchura() {
    return LARGO_MONEDA;
}