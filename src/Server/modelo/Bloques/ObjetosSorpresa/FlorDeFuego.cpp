#include "src/Server/modelo/PosicionFija.hpp"
#include "FlorDeFuego.h"

const int CANTIDAD_COLORES = 4,ANCHO_FLOR = 16;

FlorDeFuego::FlorDeFuego(int posX, int posY) {
    posicionFija = PosicionFija(posX,posY);
    usado = false;
    int color = rand()%CANTIDAD_COLORES;
    recorte = {color*ANCHO_FLOR,0,ANCHO_FLOR,ANCHO_FLOR};
}

void FlorDeFuego::usarse(Mario *mario) {
    //if(colision de mario con flor, mario no es de fuego, y la flor no esta usada){
        mario->hacerseDeFuego();
        usado = true;
    //}
}
