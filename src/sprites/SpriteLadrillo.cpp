
#include "SpriteLadrillo.h"

SpriteLadrillo::SpriteLadrillo(){
	direccionTextura = "resources/BloqueLadrillo.png";
	this->rectanguloLadrillo.x = 0;
	this->rectanguloLadrillo.y = 0;
	this->rectanguloLadrillo.w = 16;
	this->rectanguloLadrillo.h = 32;

}

string SpriteLadrillo::obtenerDireccionSprite(){
	return this->direccionTextura;
}

void SpriteLadrillo::actualizarSprite(){
	// Por ahora no se actualiza este sprite (queda en estado 0)
}

//ESTO YA NO ES NECESARIO
int SpriteLadrillo::obtenerPosicionXRectangulo(){
	return rectanguloLadrillo.x;
}


SDL_Rect SpriteLadrillo::obtenerRectanguloActual(){
	return rectanguloLadrillo;
}
