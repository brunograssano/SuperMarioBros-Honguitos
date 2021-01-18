#include "RecorteCoffinMario.hpp"
#define ESTADOS_COFFIN 3
#define DESPLAZAMIENTO_X 75
#define ALTO_COFFIN 32
#define ANCHO_COFFIN 70

RecorteCoffinMario::RecorteCoffinMario(){
	estadoActual = 0;
	ciclos = 0;
	posicionX = 0;
	inicializarEstados(ESTADOS_COFFIN,DESPLAZAMIENTO_X,ALTO_COFFIN,ANCHO_COFFIN);
}

void RecorteCoffinMario::actualizarSprite(){
	if(ciclos>=20){
		estadoActual == 2? estadoActual = 0 : estadoActual++;
		posicionX+=5;
		ciclos = 0;
	}
	else{
		ciclos++;
	}
}

int RecorteCoffinMario::obtenerPosicionX() const{
	return posicionX;
}

SDL_Rect RecorteCoffinMario::obtenerRecorte(int recorte) {
    return Recorte::obtenerRecorte(estadoActual);
}
