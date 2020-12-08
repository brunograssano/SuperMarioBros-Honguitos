#include "SpriteCoffinMario.hpp"


SpriteCoffinMario::SpriteCoffinMario(){
	direccionTextura = "resources/Imagenes/Personajes/MarioCoffinDance.png";
	estadoActual = 0;
	ciclos = 0;
	posicionX = 0;

	int corrimientoEnImagen = 0;
	for(int i=0;i<3;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = 70;
		estadosPosibles[i].h = 32;
		corrimientoEnImagen+= 75;
	}
}

SDL_Rect SpriteCoffinMario::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}

void SpriteCoffinMario::actualizarSprite(){
	if(ciclos>=20){
		estadoActual == 2? estadoActual = 0 : estadoActual++;
		posicionX+=5;
		ciclos = 0;
	}
	else{
		ciclos++;
	}
}

int SpriteCoffinMario::obtenerPosicionX(){
	return posicionX;
}

