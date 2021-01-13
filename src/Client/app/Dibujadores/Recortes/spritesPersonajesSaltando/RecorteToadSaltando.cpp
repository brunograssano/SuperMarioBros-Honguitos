
#include "RecorteToadSaltando.hpp"


RecorteToadSaltando::RecorteToadSaltando(){
	estadoActual = 0;
	int corrimientoEnImagen = 0;
	for(auto & estadosPosible : estadosPosibles){
		estadosPosible.x = corrimientoEnImagen;
		estadosPosible.y = 0;
		estadosPosible.w = 19;
		estadosPosible.h = 28;
		corrimientoEnImagen+= 20;
	}
}



void RecorteToadSaltando::actualizarSprite(){
	if(ciclos%5==0){
		estadoActual++;
		if(estadoActual==11 && ciclos%5==0){
			estadoActual=0;
		}
	}
	ciclos++;
}

SDL_Rect RecorteToadSaltando::obtenerRecorte(int recorte){
	return estadosPosibles[estadoActual];
}

int RecorteToadSaltando::obtenerAltura() {
    return estadosPosibles[estadoActual].h;
}

int RecorteToadSaltando::obtenerAnchura() {
    return estadosPosibles[estadoActual].w;
}



