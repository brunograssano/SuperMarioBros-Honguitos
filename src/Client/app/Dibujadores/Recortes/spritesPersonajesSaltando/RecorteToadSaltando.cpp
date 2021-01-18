#include "RecorteToadSaltando.hpp"
#define ESTADOS_TOAD 12
#define DESPLAZAMIENTO_X 20
#define ALTO 28
#define ANCHO 19

RecorteToadSaltando::RecorteToadSaltando(){
	estadoActual = 0;
	inicializarEstados(ESTADOS_TOAD,DESPLAZAMIENTO_X,ALTO,ANCHO);
}

void RecorteToadSaltando::actualizarSprite(){
	if(ciclos%5==0){
		estadoActual++;
		if(estadoActual==11 && ciclos%5==0){
			estadoActual=0;
		}
	}
	ciclos++;
}

SDL_Rect RecorteToadSaltando::obtenerRecorte(int recorte) {
    return Recorte::obtenerRecorte(estadoActual);
}
