


#include "SpriteGoomba.hpp"

#include <iostream>

SpriteGoomba::SpriteGoomba(int tipo){
	direccionTextura = "resources/Imagenes/Personajes/Goombas.png";
	estadoActual = 0;
	ciclos=0;
	int corrimientoEnImagen = 0;
	for(int i=0;i<3;i++){
		estadosPosibles[i].x = corrimientoEnImagen;
		estadosPosibles[i].y = tipo*16;
		estadosPosibles[i].w = 16;
		estadosPosibles[i].h = 16;
		corrimientoEnImagen+= 16;
	}
}

void SpriteGoomba::actualizarSprite(){
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
