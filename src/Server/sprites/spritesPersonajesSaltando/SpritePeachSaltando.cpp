#include "SpritePeachSaltando.hpp"


SpritePeachSaltando::SpritePeachSaltando(){
	direccionTextura = "resources/Imagenes/PersonajesSaltando/PeachSaltando.png";
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


