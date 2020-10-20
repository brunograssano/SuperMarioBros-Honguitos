

#include "SpriteKoopa.h"

SpriteKoopa::SpriteKoopa(string direccionImagen){
	direccionTextura = direccionImagen;
	//alto = 40;
	//ancho = 35;
	estadoActual = 0;
	ciclos=0;
	cambio=false;
	int corrimientoEnImagen=0;
	for(int i=0;i<3;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = 16;
		estadosPosibles[i].h = 32;
		corrimientoEnImagen+= 16;
	}
}

void SpriteKoopa::actualizarSprite(){
	if(ciclos>=20){
		estadoActual = 1;
		ciclos = 0;
	}
	else if(ciclos>=10){
		estadoActual = 0;
	}
	ciclos++;
}

int SpriteKoopa::obtenerPosicionXRectangulo(){
	return estadosPosibles[estadoActual].x;
}


SDL_Rect SpriteKoopa::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];//Da lo mismo cual devolvamos aca, cambia a partir de donde estaria la imagen
}
