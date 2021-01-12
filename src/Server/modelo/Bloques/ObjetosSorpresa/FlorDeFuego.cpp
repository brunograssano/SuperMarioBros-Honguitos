#include "src/Server/modelo/PosicionFija.hpp"
#include "FlorDeFuego.h"

const int CANTIDAD_COLORES = 4,ANCHO_FLOR = 16;

FlorDeFuego::FlorDeFuego(int posX, int posY) {
    posicionFija = PosicionFija(posX,posY);
    usado = false;
    int color = rand()%CANTIDAD_COLORES;
    recorte = {color*ANCHO_FLOR,0,ANCHO_FLOR,ANCHO_FLOR};
    agarraronFlor = false;
}

void FlorDeFuego::usarse(Mario *mario) {
    if(agarraronFlor && !usado){
        mario->hacerseDeFuego();
        usado = true;
    }
}
