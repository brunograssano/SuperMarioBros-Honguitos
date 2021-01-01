
#include "SpriteMoneda.hpp"

SpriteMoneda::SpriteMoneda(){
	this->direccionTextura = "resources/Imagenes/Bloques/Monedas.png";
	this->ciclos = 0;
	this->estadoActual = 2;
	int desplazamiento = 0;
	for(auto & estadosPosible : this->estadosPosibles){
		estadosPosible.x = desplazamiento;
		estadosPosible.y = 0;
		estadosPosible.w = 16;
		estadosPosible.h = 17;
		desplazamiento += 16;
	}
}


void SpriteMoneda::actualizarSprite(){
	if(ciclos>=40){
		estadoActual = 3;
		ciclos = 0;
	}else if(ciclos>=30){
		estadoActual = 2;
	}else if(ciclos>=20){
		estadoActual = 1;
	}else if(ciclos>=10){
		estadoActual = 0;
	}
	ciclos++;
}



SDL_Rect SpriteMoneda::obtenerRectanguloActual(){
	return estadosPosibles[estadoActual];
}

