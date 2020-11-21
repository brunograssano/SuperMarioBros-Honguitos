
#include "SpriteLadrillo.hpp"

SpriteLadrillo::SpriteLadrillo(int tipo){
	this->direccionTextura = "resources/Imagenes/Bloques/Bloques.png";
	this->rectanguloLadrillo.x = 0;
	this->rectanguloLadrillo.y = tipo*16;
	this->rectanguloLadrillo.w = 16;
	this->rectanguloLadrillo.h = 16;

}

SpriteLadrillo::SpriteLadrillo(){
	direccionTextura = "resources/Imagenes/Bloques/BloqueLadrillo.png";
	this->rectanguloLadrillo.x = 0;
	this->rectanguloLadrillo.y = 0;
	this->rectanguloLadrillo.w = 16;
	this->rectanguloLadrillo.h = 16;

}

void SpriteLadrillo::actualizarSprite(){
	// Por ahora no se actualiza este sprite (queda en estado 0)
}


SDL_Rect SpriteLadrillo::obtenerRectanguloActual(){
	return rectanguloLadrillo;
}
