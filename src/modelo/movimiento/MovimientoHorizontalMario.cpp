#include "MovimientoHorizontalMario.h"

const float SPRINT_ACELERACION_HORIZONTAL = 150;
const float MAXIMA_VELOCIDAD_HORIZONTAL = 150;

const float COEFICIENTE_DE_TIEMPO = 0.16;

const int TERRENO_LIMITE_DERECHO_MAX = 8177;
const int TERRENO_LIMITE_DERECHO_MIN = 0;


bool estaAcelerando(float aceleracion){
	return(aceleracion > 1e-4 || aceleracion < -1e-4);
}

MovimientoHorizontalMario::MovimientoHorizontalMario(){
	aceleracionX = 0;
	velocidadX = 0;
	limite_terreno_izq_actual = TERRENO_LIMITE_DERECHO_MIN;
}

void MovimientoHorizontalMario::aceleraraDerecha(){
	if(!estaAcelerando(this->aceleracionX)){
		this->aceleracionX = SPRINT_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX < 0){
		this->velocidadX = 0;
		this->aceleracionX = SPRINT_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX < SPRINT_ACELERACION_HORIZONTAL){
		this->aceleracionX = SPRINT_ACELERACION_HORIZONTAL;
	}
}

void MovimientoHorizontalMario::aceleraraIzquierda(){
	if(!estaAcelerando(this->aceleracionX)){
		this->aceleracionX = -1*SPRINT_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX > 0){
		this->velocidadX = 0;
		this->aceleracionX = -1*SPRINT_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX > -1*SPRINT_ACELERACION_HORIZONTAL){
		this->aceleracionX = -1*SPRINT_ACELERACION_HORIZONTAL;
	}
}

void MovimientoHorizontalMario::actualizarVelocidad(){
	this->velocidadX += this->aceleracionX*COEFICIENTE_DE_TIEMPO;
	if(this->velocidadX > MAXIMA_VELOCIDAD_HORIZONTAL){
		this->velocidadX = MAXIMA_VELOCIDAD_HORIZONTAL;
	}else if (this->velocidadX < -1*MAXIMA_VELOCIDAD_HORIZONTAL){
		this->velocidadX = -1*MAXIMA_VELOCIDAD_HORIZONTAL;
	}
}

void MovimientoHorizontalMario::aplicarCoeficienteDeRozamiento(){
	if(this->velocidadX < 7 && this->velocidadX > -7){
		this->velocidadX = 0;
		this->aceleracionX = 0;
	}else if(this->velocidadX > 0){
		this->aceleracionX = -1*SPRINT_ACELERACION_HORIZONTAL/50;
	}else if(this->velocidadX < 0){
		this->aceleracionX = SPRINT_ACELERACION_HORIZONTAL/50;
	}
}

float calcularDesplazamiento(float velocidad, float unidadDeTiempo){
	return(velocidad* unidadDeTiempo);
}

bool MovimientoHorizontalMario::estaQuieto(){
	return(velocidadX < 3 && velocidadX > -3);
}

void MovimientoHorizontalMario::mover(PosicionMovil* posicion){
	actualizarVelocidad();
	float desplazamientoX = calcularDesplazamiento(this->velocidadX, COEFICIENTE_DE_TIEMPO);
	int posHorizontalSiguiente = posicion->obtenerPosX()  + desplazamientoX;
	if (posHorizontalSiguiente > this->limite_terreno_izq_actual && posHorizontalSiguiente < TERRENO_LIMITE_DERECHO_MAX) {
		posicion->moverHorizontal(desplazamientoX);
	}
	aplicarCoeficienteDeRozamiento();
}
