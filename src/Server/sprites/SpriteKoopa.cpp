
#include "SpriteKoopa.hpp"
#define MUERTO 2

SpriteKoopa::SpriteKoopa(int tipo){
	direccionTextura = "resources/Imagenes/Personajes/Koopas.png";
	estadoActual = 0;
	ciclos=0;
	int corrimientoEnImagen=0;
	for(auto & estadosPosible : estadosPosibles){
		estadosPosible.x = corrimientoEnImagen;
		estadosPosible.y = tipo*16;
		estadosPosible.w = 16;
		estadosPosible.h = 24;
		corrimientoEnImagen+= 16;
	}
}

void SpriteKoopa::actualizarSprite(){
    if(estadoActual == MUERTO){
        return;
    }
    if(ciclos>=20){
		estadoActual = 1;
		ciclos = 0;
	}
	else if(ciclos>=10){
		estadoActual = 0;
	}
	ciclos++;
}


SDL_Rect SpriteKoopa::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}

void SpriteKoopa::morir() {
    estadoActual = MUERTO;  // VER CON CUAL OPCION NOS QUEDAMOS DEL SPRITE
}
