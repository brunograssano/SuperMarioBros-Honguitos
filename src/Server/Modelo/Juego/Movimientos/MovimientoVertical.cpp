#include "MovimientoVertical.hpp"

const float COEFICIENTE_DE_TIEMPO = 0.16, GRAVEDAD_DEFAULT = 9.8;

MovimientoVertical::MovimientoVertical(float fuerza){
	this->velocidadY = 0;
	this->fuerza = fuerza;
	this->gravedad = GRAVEDAD_DEFAULT;
}

MovimientoVertical::MovimientoVertical(float fuerza, float gravedad) {
    this->velocidadY = 0;
    this->fuerza = fuerza;
    this->gravedad = gravedad;
}

void MovimientoVertical::saltar(Terreno* terreno){
    this->velocidadY = terreno->amortiguarVelocidad(velocidadY);
    this->velocidadY += terreno->obtenerImpulsoVertical(fuerza);
}

void MovimientoVertical::aplicarGravedad(){
	this->velocidadY -= gravedad*COEFICIENTE_DE_TIEMPO;
}

void MovimientoVertical::mover(PosicionMovil* posicion){
	float desplazamientoY = this->velocidadY*COEFICIENTE_DE_TIEMPO;
	posicion->moverVertical(desplazamientoY);
	aplicarGravedad();
}

void MovimientoVertical::setVelocidadY(int velocidad) {
    this->velocidadY = (float)velocidad;
}

void MovimientoVertical::aplicarGravedadDefault() {
    this->gravedad = GRAVEDAD_DEFAULT;
}
