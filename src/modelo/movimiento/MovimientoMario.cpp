#include "MovimientoMario.h"


const float SPRINT_ACELERACION_HORIZONTAL = 1000;
const float MAXIMA_VELOCIDAD_HORIZONTAL = 150;

const float COEFICIENTE_DE_TIEMPO = 0.15;


bool estaAcelerando(float aceleracion){
	return(aceleracion > 1e-4 || aceleracion < -1e-4);
}



MovimientoMario::MovimientoMario(){
	this->aceleracionX = 0;
	this->aceleracionY = 0;
	this->velocidadX = 0;
	this->velocidadY = 0;
}

void MovimientoMario::aceleraraDerecha(){
	if(!estaAcelerando(this->aceleracionX)){
		this->aceleracionX = SPRINT_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX < 0){
		this->velocidadX = 0;
		this->aceleracionX = SPRINT_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX < SPRINT_ACELERACION_HORIZONTAL){
		this->aceleracionX = SPRINT_ACELERACION_HORIZONTAL;
	}
}

void MovimientoMario::aceleraraIzquierda(){
	if(!estaAcelerando(this->aceleracionX)){
		this->aceleracionX = -1*SPRINT_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX > 0){
		this->velocidadX = 0;
		this->aceleracionX = -1*SPRINT_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX > -1*SPRINT_ACELERACION_HORIZONTAL){
		this->aceleracionX = -1*SPRINT_ACELERACION_HORIZONTAL;
	}
}

void MovimientoMario::saltar(){
	this->velocidadY = 70;
}


void MovimientoMario::aplicarCoeficienteDeRozamiento(){
	if(this->velocidadX < 7 && this->velocidadX > -7){
		this->velocidadX = 0;
		this->aceleracionX = 0;
	}else if(this->velocidadX > 0){
		this->aceleracionX = -1*SPRINT_ACELERACION_HORIZONTAL/80;
	}else if(this->velocidadX < 0){
		this->aceleracionX = SPRINT_ACELERACION_HORIZONTAL/80;
	}
}


void MovimientoMario::aplicarGravedad(){
	this->velocidadY -= 9.8*0.16;
}



void MovimientoMario::actualizarVelocidad(){
	this->velocidadX += this->aceleracionX*COEFICIENTE_DE_TIEMPO;
	if(this->velocidadX > MAXIMA_VELOCIDAD_HORIZONTAL){
		this->velocidadX = MAXIMA_VELOCIDAD_HORIZONTAL;
	}else if (this->velocidadX < -1*MAXIMA_VELOCIDAD_HORIZONTAL){
		this->velocidadX = -1*MAXIMA_VELOCIDAD_HORIZONTAL;
	}
}

float MovimientoMario::calcularDesplazamientoHorizontal(float unidadDeTiempo){
	return(this->velocidadX * unidadDeTiempo);
}
float MovimientoMario::calcularDesplazamientoVertical(float unidadDeTiempo){
	return(this->velocidadY * unidadDeTiempo);
}
