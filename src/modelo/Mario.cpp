#include "Mario.h"
#include <cmath>

const int COORDENADA_X_DEFAULT = 20;
const int COORDENADA_Y_DEFAULT = 0;
const int MINIMO_COORDENADA_Y = 0;

const int MOVIMIENTO_X_DEFAULT = 5;
const int MOVIMIENTO_Y_DEFAULT = 5;

const float PASO_ACELERACION_HORIZONTAL = 5;
const float COEFICIENTE_SOBREACELERACION_HORIZONTAL = 5;
const float MAXIMA_ACELERACION_HORIZONTAL = 1000;

const float MAXIMA_VELOCIDAD_HORIZONTAL = 150;

const float COEFICIENTE_DE_TIEMPO = 0.15;

Mario::Mario(){
	this->posicion = new PosicionMovil(COORDENADA_X_DEFAULT,COORDENADA_Y_DEFAULT, MINIMO_COORDENADA_Y);
	this->puntos=0;
	this->cantidadMonedas=0;
	this->movimiento = new MovimientoMario();
	this->estaSaltando = false;
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
}

void Mario::moveraAbajo(){
}

void Mario::aceleraraIzquierda(){
	this->movimiento->aceleraraIzquierda();
}

void Mario::aceleraraDerecha(){
	this->movimiento->aceleraraDerecha();
}

void Mario::actualizarPosicion(){
	this->movimiento->mover(this->posicion);
	if(this->posicion->obtenerPosY() == MINIMO_COORDENADA_Y){ //TODO Ojo cuando vayamos a trabajar con floats... y el "==". Cambiar por un intervalo.
		this->movimiento->setVelocidadY(0);
		this->estaSaltando = false;
	}
}
void Mario::saltar(){
	if(!this->estaSaltando){
		this->movimiento->saltar();
		this->estaSaltando = true;		//TODO Hacer un patrón State en Mario o en Movimiento.
	}
}

Mario::~Mario(){
	delete this->posicion;
	delete this->movimiento;
}
