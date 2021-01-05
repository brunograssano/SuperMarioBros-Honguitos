#include "SpriteGoomba.hpp"
#define MUERTO 2

SpriteGoomba::SpriteGoomba(int tipo){
	direccionTextura = "resources/Imagenes/Personajes/Goombas.png";
	estadoActual = 0;
	ciclos=0;
	int corrimientoEnImagen = 0;
	for(auto & estadosPosible : estadosPosibles){
		estadosPosible.x = corrimientoEnImagen;
		estadosPosible.y = tipo*16;
		estadosPosible.w = 16;
		estadosPosible.h = 16;
		corrimientoEnImagen+= 16;
	}
}

void SpriteGoomba::actualizarSprite(){
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

SDL_Rect SpriteGoomba::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}

void SpriteGoomba::morir() {
    estadoActual = MUERTO;
}
