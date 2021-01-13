#include "SpriteBolaDeFuego.hpp"

#define MAX_ESTADOS_NO_EXPLOTO 3
#define ESTADO_EXPLOTO 4
#define MAX_ESTADO_EXPLOTO 6
#define ESTADO_INICIAL 0

SpriteBolaDeFuego::SpriteBolaDeFuego() {
    this->direccionTextura = "resources/Imagenes/Objetos/BolaDeFuego.png";
    this->ciclos = 0;
    this->estadoActual = ESTADO_INICIAL;
    this->exploto = false;
    this->_terminoDeExplotar = false;
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
    if(estadoActual > MAX_ESTADOS_NO_EXPLOTO && !exploto){
        estadoActual = ESTADO_INICIAL;
    }else if(exploto && estadoActual > MAX_ESTADO_EXPLOTO){
        _terminoDeExplotar = true;
        estadoActual = MAX_ESTADO_EXPLOTO;
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

void SpriteBolaDeFuego::explotar() {
    estadoActual = ESTADO_EXPLOTO;
    exploto = true;
}

bool SpriteBolaDeFuego::terminoDeExplotar() {
    return _terminoDeExplotar;
}
