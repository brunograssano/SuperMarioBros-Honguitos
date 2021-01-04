#include "SpriteCoffinMario.hpp"


SpriteCoffinMario::SpriteCoffinMario(){
	direccionTextura = "resources/Imagenes/Personajes/MarioCoffinDance.png";
	estadoActual = 0;
	ciclos = 0;
	posicionX = 0;

	int corrimientoEnImagen = 0;
	for(auto & estadosPosible : estadosPosibles){
		estadosPosible.x = corrimientoEnImagen;
		estadosPosible.y = 0;
		estadosPosible.w = 70;
		estadosPosible.h = 32;
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

int SpriteCoffinMario::obtenerPosicionX() const{
	return posicionX;
}

