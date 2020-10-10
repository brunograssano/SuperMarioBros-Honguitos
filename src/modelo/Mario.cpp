#include "Mario.h"
#include <cmath>

const int COORDENADA_X_DEFAULT = 20;
const int COORDENADA_Y_DEFAULT = 20;

const int MOVIMIENTO_X_DEFAULT = 5;
const int MOVIMIENTO_Y_DEFAULT = 5;

const float PASO_ACELERACION_HORIZONTAL = 5;
const float COEFICIENTE_SOBREACELERACION_HORIZONTAL = 5;
const float MAXIMA_ACELERACION_HORIZONTAL = 1000;

const float MAXIMA_VELOCIDAD_HORIZONTAL = 150;

const float COEFICIENTE_DE_TIEMPO = 0.15;

Mario::Mario(){
	this->posicion = new PosicionMovil(COORDENADA_X_DEFAULT,COORDENADA_Y_DEFAULT);
	this->puntos=0;
	this->cantidadMonedas=0;
}


void Mario::mover(Movimiento* unMovimiento){
	unMovimiento->mover(this->posicion);
}

int Mario::obtenerPosicionX(){
	return posicion->obtenerPosX();
}

int Mario::obtenerPosicionY(){
	return posicion->obtenerPosY();
}

int Mario::obtenerPuntos(){
	return puntos;
}

void Mario::agregarPuntos(int unosPuntos){
	puntos+=unosPuntos;
}

int Mario::obtenerMonedas(){
	return cantidadMonedas;
}

void Mario::agregarMoneda(){
	cantidadMonedas++;
}

void Mario::moveraArriba(){
	this->posicion->moverVertical(MOVIMIENTO_Y_DEFAULT);
}
void Mario::moveraAbajo(){
	this->posicion->moverVertical(-1*MOVIMIENTO_Y_DEFAULT);
}

void Mario::aceleraraIzquierda(){
	if(this->aceleracionX < 1e-7 && this->aceleracionX > -1e-7){
		this->aceleracionX = -1*MAXIMA_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX > 0){
		this->velocidadX = 0;
		this->aceleracionX = -1*MAXIMA_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX > -1*MAXIMA_ACELERACION_HORIZONTAL){
		this->aceleracionX = -1*MAXIMA_ACELERACION_HORIZONTAL;
	}
}

void Mario::aceleraraDerecha(){
	if(this->aceleracionX < 1e-7 && this->aceleracionX > -1e-7){
		this->aceleracionX = MAXIMA_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX < 0){
		this->velocidadX = 0;
		this->aceleracionX = MAXIMA_ACELERACION_HORIZONTAL;
	}else if(this->aceleracionX < MAXIMA_ACELERACION_HORIZONTAL){
		this->aceleracionX = MAXIMA_ACELERACION_HORIZONTAL;
	}
}

void Mario::aplicarCoeficienteDeRozamiento(){
	if(this->velocidadX < 7 && this->velocidadX > -7){
		this->velocidadX = 0;
	}else if(this->velocidadX > 0){
		this->aceleracionX = -1*MAXIMA_ACELERACION_HORIZONTAL/10;
	}else if(this->velocidadX < 0){
		this->aceleracionX = MAXIMA_ACELERACION_HORIZONTAL/10;
	}
}

void Mario::actualizarVelocidad(){
	this->velocidadX += this->aceleracionX*COEFICIENTE_DE_TIEMPO;
	if(this->velocidadX > MAXIMA_VELOCIDAD_HORIZONTAL){
		this->velocidadX = MAXIMA_VELOCIDAD_HORIZONTAL;
	}else if (this->velocidadX < -1*MAXIMA_VELOCIDAD_HORIZONTAL){
		this->velocidadX = -1*MAXIMA_VELOCIDAD_HORIZONTAL;
	}
}

void Mario::actualizarPosicion(){
	this->aplicarCoeficienteDeRozamiento();
	this->actualizarVelocidad();
	float desplazamiento = this->velocidadX*0.016;
	this->posicion->moverHorizontal(desplazamiento);
}


Mario::~Mario(){
	delete this->posicion;
}

