#include "SpriteBolaDeFuego.hpp"

#define MAX_ESTADO_BOLA_DE_FUEGO 3
#define ESTADO_INICIAL 0

SpriteBolaDeFuego::SpriteBolaDeFuego() {
    this->direccionTextura = "resources/Imagenes/Objetos/BolaDeFuego.png";
    this->ciclos = 0;
    this->estadoActual = ESTADO_INICIAL;

    int corrimientoEnImagen = 0;
    for(auto & estadosPosible : estadosPosibles){
        estadosPosible.x = corrimientoEnImagen;
        estadosPosible.y = 0;
        estadosPosible.w = 31;
        estadosPosible.h = 32;
        corrimientoEnImagen+= 32;
    }
}


void SpriteBolaDeFuego::cambiarSprite() {
    estadoActual++;
    if(estadoActual > MAX_ESTADO_BOLA_DE_FUEGO){
        estadoActual = ESTADO_INICIAL;
    }
}

void SpriteBolaDeFuego::actualizarSprite() {
    if(ciclos >= CICLOS_PARA_CAMBIO) {
        cambiarSprite();
        ciclos = 0;
    }
    ciclos++;
}

SDL_Rect SpriteBolaDeFuego::obtenerRectanguloActual() {
    return estadosPosibles[estadoActual];
}
