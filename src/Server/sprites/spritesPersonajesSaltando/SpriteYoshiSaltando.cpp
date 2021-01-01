


#include "SpriteYoshiSaltando.hpp"


SpriteYoshiSaltando::SpriteYoshiSaltando(){
	direccionTextura = "resources/Imagenes/PersonajesSaltando/YoshiSaltando.png";
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



void SpriteYoshiSaltando::actualizarSprite(){
	if(ciclos%5==0){
		estadoActual++;
		if(estadoActual==15 && ciclos%5==0){
			estadoActual=0;
		}
	}
	ciclos++;
}

SDL_Rect SpriteYoshiSaltando::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}


