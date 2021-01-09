#include "MovimientoHorizontal.hpp"

const float COEFICIENTE_DE_TIEMPO = 1;

bool velocidadBaja(float velocidad){
	return(velocidad < 0.5 && velocidad > -0.5);
}

MovimientoHorizontal::MovimientoHorizontal(float maximaVelocidad, float aceleracion){
	this->aceleracionX = aceleracion;
	this->maximaVelocidadX = maximaVelocidad;
	this->velocidadX = 0;
}

void MovimientoHorizontal::aceleraraDerecha(Terreno* terreno){
	float impulso = terreno->obtenerImpulsoHorizontal(this->aceleracionX);
	if(velocidadBaja(velocidadX)){
		velocidadX += 2*impulso;
	}
	if(velocidadX > maximaVelocidadX){
		velocidadX = maximaVelocidadX;
	}else{
		velocidadX += impulso;
	}
}

void MovimientoHorizontal::aceleraraIzquierda(Terreno* terreno){
	float impulso = terreno->obtenerImpulsoHorizontal(this->aceleracionX);
	if(velocidadBaja(velocidadX)){
		velocidadX -= 2*impulso ;
	}
	if(velocidadX < -1*maximaVelocidadX){
		velocidadX = -1*maximaVelocidadX;
	}else{
		velocidadX -= impulso ;
	}
}

float calcularDesplazamiento(float velocidad, float unidadDeTiempo){
	return(velocidad* unidadDeTiempo);
}

bool MovimientoHorizontal::estaQuieto(){
	return(velocidadBaja(velocidadX));
}

void MovimientoHorizontal::mover(PosicionMovil* posicion, Terreno* terreno){
	float desplazamientoX = velocidadX*COEFICIENTE_DE_TIEMPO;
	posicion->moverHorizontal(desplazamientoX);
	velocidadX = terreno->aplicarCoeficienteDeRozamiento(velocidadX);
	if(velocidadBaja(velocidadX)){
		velocidadX = 0;
	}
}

float MovimientoHorizontal::obtenerVelocidadXActual() {
    return this->velocidadX;
}
