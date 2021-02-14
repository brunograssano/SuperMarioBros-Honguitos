#include "SpriteLadrillo.hpp"
#define TODO_ROTO 4


SpriteLadrillo::SpriteLadrillo(){
    estadoActual = 0;
    estadoAnterior = 0;
}

void SpriteLadrillo::actualizarSprite(){
}

void SpriteLadrillo::usarse() {
    if(estadoActual >= TODO_ROTO){
        return;
    }
    estadoActual++;
    estadoAnterior = estadoActual - 1;
}

bool SpriteLadrillo::cambioElSprite() {
    bool cambio = estadoAnterior != estadoActual;
    estadoAnterior = estadoActual;
    return cambio;
}
