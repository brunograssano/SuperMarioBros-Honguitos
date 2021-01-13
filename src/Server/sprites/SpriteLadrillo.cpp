#include "SpriteLadrillo.hpp"
#define TODO_ROTO 4


SpriteLadrillo::SpriteLadrillo(){
    estadoActual = 0;
    estadoAnterior = 0;
}

void SpriteLadrillo::actualizarSprite(){
}

SDL_Rect SpriteLadrillo::obtenerRectanguloActual(){ // TODO BORRAR ESTE METODO
	return {0,0,0,0};
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
