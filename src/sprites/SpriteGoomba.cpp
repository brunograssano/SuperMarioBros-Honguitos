


#include "SpriteGoomba.h"

SpriteGoomba::SpriteGoomba(string direccionImagen){
	direccionTextura = direccionImagen;
	alto = 40;
	ancho = 35;
	estadoActual = 0;
	ciclos=0;
	cambio=false;
	int corrimientoEnImagen = 0;
	for(int i=0;i<3;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 450; //Recordar que en los rectangulos de los sprites los pixeles en Y se cuentan al reves
		estadosPosibles[i].w = 32;
		estadosPosibles[i].h = 64;
		corrimientoEnImagen+= 16;
	}
}

void SpriteGoomba::actualizarSprite(){
	if(ciclos>=20){
		estadoActual = 1;
		ciclos = 0;
	}
	else if(ciclos>=10){
		estadoActual = 0;
	}
	ciclos++;
}

int SpriteGoomba::obtenerPosicionXRectangulo(){
	return estadosPosibles[estadoActual].x;
}


SDL_Rect SpriteGoomba::obtenerRectanguloActual(){
	return estadosPosibles[0];//Da lo mismo cual devolvamos aca, cambia a partir de donde estaria la imagen
}
