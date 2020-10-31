


#include "SpriteYoshiSaltando.hpp"


SpriteYoshiSaltando::SpriteYoshiSaltando(){
	direccionTextura = "resources/PersonajesSaltando/YoshiSaltando.png";
	estadoActual = 0;
	int corrimientoEnImagen = 0;
	for(int i=0;i<16;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = 0;
		estadosPosibles[i].w = 20;
		estadosPosibles[i].h = 29;
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


