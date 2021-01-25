#include "SpriteBolaDeFuego.hpp"

#define MAX_ESTADOS_NO_EXPLOTO 3
#define ESTADO_EXPLOTO 4
#define MAX_ESTADO_EXPLOTO 6
const int CICLOS_PARA_CAMBIO = 5;
#define ESTADO_INICIAL 0

SpriteBolaDeFuego::SpriteBolaDeFuego() {
    this->ciclos = 0;
    this->estadoActual = ESTADO_INICIAL;
    this->exploto = false;
    this->_terminoDeExplotar = false;
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

void SpriteBolaDeFuego::explotar() {
    estadoActual = ESTADO_EXPLOTO;
    exploto = true;
}

bool SpriteBolaDeFuego::terminoDeExplotar() const {
    return _terminoDeExplotar;
}
