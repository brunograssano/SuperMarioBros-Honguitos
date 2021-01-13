#include "RecortePeachSaltando.hpp"

RecortePeachSaltando::RecortePeachSaltando(){
	estadoActual = 0;
	int corrimientoEnImagen = 0;
	for(auto & estadosPosible : estadosPosibles){
		estadosPosible.x = corrimientoEnImagen;
		estadosPosible.y = 0;
		estadosPosible.w = 19;
		estadosPosible.h = 30;
		corrimientoEnImagen+= 20;
	}
}



void RecortePeachSaltando::actualizarSprite(){
	if(ciclos%5==0){
		estadoActual++;
		if(estadoActual==13 && ciclos%5==0){
			estadoActual=0;
		}
	}
	ciclos++;
}

SDL_Rect RecortePeachSaltando::obtenerRecorte(int recorte){
	return estadosPosibles[estadoActual];
}

int RecortePeachSaltando::obtenerAnchura() {
    return estadosPosibles[estadoActual].h;
}

int RecortePeachSaltando::obtenerAltura() {
    return estadosPosibles[estadoActual].w;
}


