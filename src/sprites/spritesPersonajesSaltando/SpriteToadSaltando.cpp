
#include "SpriteToadSaltando.hpp"


SpriteToadSaltando::SpriteToadSaltando(){
	direccionTextura = "resources/Imagenes/PersonajesSaltando/HonguitoSaltando.png";
	estadoActual = 0;
	int corrimientoEnImagen = 0;
	for(int i=0;i<12;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = 19;
		estadosPosibles[i].h = 28;
		corrimientoEnImagen+= 20;
	}
}



void SpriteToadSaltando::actualizarSprite(){
	if(ciclos%5==0){
		estadoActual++;
		if(estadoActual==11 && ciclos%5==0){
			estadoActual=0;
		}
	}
	ciclos++;
}

SDL_Rect SpriteToadSaltando::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}



