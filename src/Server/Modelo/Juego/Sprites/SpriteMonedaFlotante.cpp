#include "SpriteMonedaFlotante.hpp"

const int CICLOS_PARA_CAMBIO = 5;
#define MAXIMO_ESTADOS 4
#define ESTADO_INICIAL 0

SpriteMonedaFlotante::SpriteMonedaFlotante() {
    estadoActual = ESTADO_INICIAL;
    this->ciclos = 0;
}

int SpriteMonedaFlotante::obtenerEstadoActual() {
    return estadoActual;
}

void SpriteMonedaFlotante::actualizarSprite() {
    ciclos++;
    if(ciclos >= CICLOS_PARA_CAMBIO) {
        cambiarSprite();
        ciclos = 0;
    }
}

void SpriteMonedaFlotante::cambiarSprite() {
    estadoActual++;
    if(estadoActual >= MAXIMO_ESTADOS){
        estadoActual = ESTADO_INICIAL;
    }
}

