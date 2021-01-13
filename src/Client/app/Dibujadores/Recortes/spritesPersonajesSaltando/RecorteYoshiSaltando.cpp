#include "RecorteYoshiSaltando.hpp"

RecorteYoshiSaltando::RecorteYoshiSaltando(){
	estadoActual = 0;
	int corrimientoEnImagen = 0;
	for(auto & estadosPosible : estadosPosibles){
		estadosPosible.x = corrimientoEnImagen;
		estadosPosible.y = 0;
		estadosPosible.w = 20;
		estadosPosible.h = 29;
		corrimientoEnImagen+= 20;
	}
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

SDL_Rect RecorteYoshiSaltando::obtenerRecorte(int recorte){
	return estadosPosibles[estadoActual];
}

int RecorteYoshiSaltando::obtenerAltura() {
    return estadosPosibles[estadoActual].h;
}

int RecorteYoshiSaltando::obtenerAnchura() {
    return estadosPosibles[estadoActual].w;
}


