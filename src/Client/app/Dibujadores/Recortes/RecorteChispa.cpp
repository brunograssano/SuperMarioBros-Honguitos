#include "RecorteChispa.hpp"
#include "src/Utils/Constantes.hpp"

const int ALTO_IMAGEN_PIXEL = 22;
const int ANCHO_IMAGEN_PIXEL = 31;
const int PASO_PROXIMO_SPRITE = 32;

RecorteChispa::RecorteChispa() {
    inicializarEstados(CANTIDAD_DE_RECORTES,PASO_PROXIMO_SPRITE,ALTO_IMAGEN_PIXEL,ANCHO_IMAGEN_PIXEL);
}

SDL_Rect RecorteChispa::obtenerRecorte(int recorte) {
    return Recorte::obtenerRecorte(recorte<CANTIDAD_DE_RECORTES?recorte:recorte-CANTIDAD_DE_RECORTES);
}

int RecorteChispa::direccion(int recorte){
    return recorte<CANTIDAD_DE_RECORTES?DERECHA:IZQUIERDA;
}

int RecorteChispa::obtenerAlturaParaDibujarImagen() {
    return ALTO_CHISPA;
}

int RecorteChispa::obtenerAnchuraParaDibujarImagen() {
    return ANCHO_CHISPA;
}
