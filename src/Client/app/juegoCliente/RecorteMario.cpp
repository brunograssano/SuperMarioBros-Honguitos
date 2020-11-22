#include "RecorteMario.hpp"

const int ANCHO_IMAGEN_PIXEL = 405;
const int ALTO_IMAGEN_PIXEL = 32;
const int ANCHO_SPRITE_PIXEL = 16;
const int ALTO_SPRITE_PIXEL = 32;
const int PASO_PROXIMO_SPRITE = 30;

RecorteMario::RecorteMario(){
	int corrimientoEnImagen = 0;

	for(int i=0;i<14;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = ANCHO_SPRITE_PIXEL;
		estadosPosibles[i].h = ALTO_SPRITE_PIXEL;
		corrimientoEnImagen+= PASO_PROXIMO_SPRITE;
	}
}


SDL_Rect RecorteMario::obtenerRecorte(int recorte){
	return estadosPosibles[recorte];
}

