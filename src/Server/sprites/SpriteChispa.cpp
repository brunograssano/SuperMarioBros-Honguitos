#include "SpriteChispa.hpp"

const int CICLOS_PARA_CAMBIO = 5;
#define ESTADO_INICIAL 0

SpriteChispa::SpriteChispa(int direccion){
    this->ciclos = 0;
    this->estadoActual = ESTADO_INICIAL;
    this->direccion = direccion;
}
void SpriteChispa::cambiarSprite() {
    if(estadoActual == 3){
        estadoActual = 2;
    }else{
        estadoActual++;
    }
}

void SpriteChispa::actualizarSprite() {
    if(ciclos >= CICLOS_PARA_CAMBIO) {
        cambiarSprite();
        ciclos = 0;
    }
    ciclos++;
}

int SpriteChispa::obtenerEstadoActual() {
    if(direccion == DERECHA){
        return estadoActual;
    }else{
        return estadoActual + 4; //Implica que está mirando hacia la izquierda.
    }
}


