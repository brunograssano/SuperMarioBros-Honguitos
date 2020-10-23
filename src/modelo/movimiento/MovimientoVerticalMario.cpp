#include "MovimientoVerticalMario.h"

const float COEFICIENTE_DE_TIEMPO = 0.16;

MovimientoVerticalMario::MovimientoVerticalMario(){
	this->aceleracionY = 0;
	this->velocidadY = 0;
}
void MovimientoVerticalMario::saltar(){
	this->velocidadY = 60;
}

void MovimientoVerticalMario::aplicarGravedad(){
	this->velocidadY -= 9.8*COEFICIENTE_DE_TIEMPO;
}

void MovimientoVerticalMario::mover(PosicionMovil* posicion){
	float desplazamientoY = this->velocidadY*COEFICIENTE_DE_TIEMPO;
	posicion->moverVertical(desplazamientoY);
	aplicarGravedad();
}
