#include "SpriteSorpresa.hpp"

const int USADO = 3;

SpriteSorpresa::SpriteSorpresa(){
	direccionTextura = "resources/Imagenes/Bloques/BloqueSorpresa.png";
	estadoActual = 0;
	ciclos=0;
	int corrimientoEnImagen = 0;
	for(auto & estadosPosible : estadosPosibles){
		estadosPosible.x = corrimientoEnImagen;
		estadosPosible.y = 0;
		estadosPosible.w = 16;
		estadosPosible.h = 16;
		corrimientoEnImagen+= 16;
	}
}

void SpriteSorpresa::actualizarSprite(){
    if(estadoActual == USADO){
        return;
    }
    if(ciclos>=50){
        estadoActual = 0;
        ciclos = 0;
    }
    else if(ciclos>=40){
        estadoActual = 2;
    }
    else if(ciclos>=30){
        estadoActual = 1;
    }
    ciclos++;
}

SDL_Rect SpriteSorpresa::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}

void SpriteSorpresa::usarse() {
    estadoActual = USADO;
}

bool SpriteSorpresa::cambioElSprite() {
    return true;
}
