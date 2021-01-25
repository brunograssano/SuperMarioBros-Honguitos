#include "MovimientoVertical.hpp"

const float COEFICIENTE_DE_TIEMPO = 0.16, GRAVEDAD = 9.8;

MovimientoVertical::MovimientoVertical(float fuerza){
	this->velocidadY = 0;
	this->fuerza = fuerza;
}
void MovimientoVertical::saltar(Terreno* terreno){
    this->velocidadY = terreno->amortiguarVelocidad(velocidadY);
    this->velocidadY += terreno->obtenerImpulsoVertical(fuerza);
}

void MovimientoVertical::aplicarGravedad(){
	this->velocidadY -= GRAVEDAD*COEFICIENTE_DE_TIEMPO;
}

void MovimientoVertical::mover(PosicionMovil* posicion){
	float desplazamientoY = this->velocidadY*COEFICIENTE_DE_TIEMPO;
	posicion->moverVertical(desplazamientoY);
	aplicarGravedad();
}

void MovimientoVertical::setVelocidadY(int velocidad) {
    this->velocidadY = (float)velocidad;
}

