#include "SpriteChispa.hpp"
#include "src/Utils/Constantes.hpp"

const int CICLOS_PARA_CAMBIO = 5;
#define ESTADO_INICIAL 0

SpriteChispa::SpriteChispa(int direccion){
    this->ciclos = 0;
    this->estadoActual = ESTADO_INICIAL;
    this->espejado = direccion == IZQUIERDA;
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

bool SpriteChispa::estaEspejado() {
    return espejado;
}

