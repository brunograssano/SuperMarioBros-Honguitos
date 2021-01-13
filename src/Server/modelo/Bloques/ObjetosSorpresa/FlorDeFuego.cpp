#include "src/Server/modelo/PosicionFija.hpp"
#include "FlorDeFuego.hpp"

const int CANTIDAD_COLORES = 4,ANCHO_FLOR = 16;

FlorDeFuego::FlorDeFuego(int posX, int posY) {
    posicionFija = PosicionFija(posX,posY);
    _debeDesaparecer = false;
    int color = rand()%CANTIDAD_COLORES;
    recorte = {color*ANCHO_FLOR,0,ANCHO_FLOR,ANCHO_FLOR};
    agarraronFlor = false;
}

void FlorDeFuego::usarse(Mario *mario){}

efecto_t FlorDeFuego::serializar() {
    unsigned short x = posicionFija.obtenerPosX();
    unsigned short y = posicionFija.obtenerPosY();
    return {x,y, 0,FLOR};
}

void FlorDeFuego::actualizar() {}

int FlorDeFuego::obtenerPosicionX() {
    return posicionFija.obtenerPosX();
}
