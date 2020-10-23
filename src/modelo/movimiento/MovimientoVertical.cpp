#include "MovimientoVertical.h"

const float COEFICIENTE_DE_TIEMPO = 0.16;

MovimientoVertical::MovimientoVertical(float fuerza){
	this->velocidadY = 0;
	this->fuerza = fuerza;
}
void MovimientoVertical::saltar(Terreno* terreno){
	this->velocidadY += terreno->obtenerImpulsoVertical(fuerza);
}

void MovimientoVertical::aplicarGravedad(){
	this->velocidadY -= 9.8*COEFICIENTE_DE_TIEMPO;
}

void MovimientoVertical::mover(PosicionMovil* posicion){
	float desplazamientoY = this->velocidadY*COEFICIENTE_DE_TIEMPO;
	posicion->moverVertical(desplazamientoY);
	aplicarGravedad();
}