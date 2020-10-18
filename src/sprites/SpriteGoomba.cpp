


#include "SpriteGoomba.h"

SpriteGoomba::SpriteGoomba(string direccionImagen){
	direccionTextura = direccionImagen;
	alto = 40;
	ancho = 35;
	estadoActual = 0;
	int corrimientoEnImagen=0;
	for(int i=0;i<3;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = 16;
		estadosPosibles[i].h = 32;
		corrimientoEnImagen+= 16;
	}
}


SDL_Rect SpriteGoomba::obtenerRectanguloActual(){
	return estadosPosibles[0];
}
