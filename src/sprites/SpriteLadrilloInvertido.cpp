
#include "SpriteLadrilloInvertido.h"

SpriteLadrilloInvertido::SpriteLadrilloInvertido(){
	direccionTextura = "resources/BloqueLadrilloInvertido.png";
	this->rectanguloLadrillo.x = 0;
	this->rectanguloLadrillo.y = 0;
	this->rectanguloLadrillo.w = 16;
	this->rectanguloLadrillo.h = 16;

}

void SpriteLadrilloInvertido::actualizarSprite(){
	// Por ahora no se actualiza este sprite (queda en estado 0)
}


SDL_Rect SpriteLadrilloInvertido::obtenerRectanguloActual(){
	return rectanguloLadrillo;
}



