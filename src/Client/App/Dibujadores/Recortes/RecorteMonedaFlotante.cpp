#include "RecorteMonedaFlotante.hpp"
#include "src/Utils/Constantes.hpp"
const int ALTO_IMAGEN_PIXEL = 16;
const int ANCHO_IMAGEN_PIXEL = 16;
const int PASO_PROXIMO_SPRITE = 16;
const int CANTIDAD_DE_RECORTES = 4;

RecorteMonedaFlotante::RecorteMonedaFlotante() {
    inicializarEstados(CANTIDAD_DE_RECORTES,PASO_PROXIMO_SPRITE,ALTO_IMAGEN_PIXEL,ANCHO_IMAGEN_PIXEL);
}

int RecorteMonedaFlotante::obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) {
    return LARGO_MONEDA;
}

int RecorteMonedaFlotante::obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) {
    return LARGO_MONEDA;
}