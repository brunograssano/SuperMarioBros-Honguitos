#include "RecorteCoffinMario.hpp"


RecorteCoffinMario::RecorteCoffinMario(){
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

SDL_Rect RecorteCoffinMario::obtenerRecorte(int recorte){
	return estadosPosibles[estadoActual];
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

int RecorteCoffinMario::obtenerAltura() {
    return estadosPosibles[estadoActual].h;
}

int RecorteCoffinMario::obtenerAnchura() {
    return estadosPosibles[estadoActual].w;
}

