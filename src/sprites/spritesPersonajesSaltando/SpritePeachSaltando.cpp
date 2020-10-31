#include "SpritePeachSaltando.hpp"


SpritePeachSaltando::SpritePeachSaltando(){
	estadoActual = 0;
	int corrimientoEnImagen = 0;
	for(int i=0;i<14;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = 27;
		estadosPosibles[i].h = 40;
		corrimientoEnImagen+= 27;
	}
}



void SpritePeachSaltando::actualizarSprite(){
	if(ciclos%5==0){
		estadoActual++;
		if(estadoActual==13 && ciclos%5==0){
			estadoActual=0;
		}
	}
	ciclos++;
}

SDL_Rect SpritePeachSaltando::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}


