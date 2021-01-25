#include "SpriteSorpresa.hpp"

const int USADO = 3;

SpriteSorpresa::SpriteSorpresa(){
    estadoActual = 0;
	ciclos=0;
}

void SpriteSorpresa::actualizarSprite(){
    if(estadoActual == USADO){
        return;
    }
    if(ciclos>=50){
        estadoActual = 0;
        ciclos = 0;
    }
    else if(ciclos>=40){
        estadoActual = 2;
    }
    else if(ciclos>=30){
        estadoActual = 1;
    }
    ciclos++;
}

void SpriteSorpresa::usarse() {
    estadoActual = USADO;
}

bool SpriteSorpresa::cambioElSprite() {
    return true;
}
