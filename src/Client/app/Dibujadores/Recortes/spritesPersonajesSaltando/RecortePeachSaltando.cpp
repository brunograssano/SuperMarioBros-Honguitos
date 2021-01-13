#include "RecortePeachSaltando.hpp"
#define ESTADOS_PEACH 14
#define DESPLAZAMIENTO_X 20
#define ALTO 30
#define ANCHO 19

RecortePeachSaltando::RecortePeachSaltando(){
	estadoActual = 0;
	inicializarEstados(ESTADOS_PEACH,DESPLAZAMIENTO_X,ALTO,ANCHO);
}

void RecortePeachSaltando::actualizarSprite(){
	if(ciclos%5==0){
		estadoActual++;
		if(estadoActual==13 && ciclos%5==0){
			estadoActual=0;
		}
	}
	ciclos++;
}

SDL_Rect RecortePeachSaltando::obtenerRecorte(int recorte) {
    return Recorte::obtenerRecorte(estadoActual);
}
