#include "RecorteYoshiSaltando.hpp"

#define ESTADOS_YOSHI 16
#define DESPLAZAMIENTO_X 20
#define ALTO 29
#define ANCHO 20

RecorteYoshiSaltando::RecorteYoshiSaltando(){
	estadoActual = 0;
	inicializarEstados(ESTADOS_YOSHI,DESPLAZAMIENTO_X,ALTO,ANCHO);
}

void RecorteYoshiSaltando::actualizarSprite(){
	if(ciclos%5==0){
		estadoActual++;
		if(estadoActual==15 && ciclos%5==0){
			estadoActual=0;
		}
	}
	ciclos++;
}

SDL_Rect RecorteYoshiSaltando::obtenerRecorte(int recorte) {
    return Recorte::obtenerRecorte(estadoActual);
}
