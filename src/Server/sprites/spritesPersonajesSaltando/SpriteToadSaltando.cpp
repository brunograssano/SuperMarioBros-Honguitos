
#include "SpriteToadSaltando.hpp"


SpriteToadSaltando::SpriteToadSaltando(){
	direccionTextura = "resources/Imagenes/PersonajesSaltando/HonguitoSaltando.png";
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



