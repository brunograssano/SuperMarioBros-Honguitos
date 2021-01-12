#include "SpriteLadrillo.hpp"
#define TODO_ROTO 4


SpriteLadrillo::SpriteLadrillo(int tipo){
    estadoActual = 0;
}

void SpriteLadrillo::actualizarSprite(){
	if(estadoActual >= TODO_ROTO){
	    return;
	}
	estadoActual++;
}


SDL_Rect SpriteLadrillo::obtenerRectanguloActual(){ // TODO BORRAR ESTE METODO
	return {0,0,0,0};
}
