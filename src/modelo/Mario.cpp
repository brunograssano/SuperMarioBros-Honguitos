#include "Mario.h"
#include <cmath>

const int COORDENADA_X_DEFAULT = 20;
const int COORDENADA_Y_DEFAULT = 0;

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
	this->movimiento = new MovimientoMario();
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
	if(this->posicion->obtenerPosY() - MOVIMIENTO_Y_DEFAULT < COORDENADA_Y_DEFAULT){
		this->posicion->moverVertical(COORDENADA_Y_DEFAULT - this->posicion->obtenerPosY());
	}else{
		this->posicion->moverVertical(-1*MOVIMIENTO_Y_DEFAULT);
	}
}

void Mario::aceleraraIzquierda(){
	this->movimiento->aceleraraIzquierda();
}

void Mario::aceleraraDerecha(){
	this->movimiento->aceleraraDerecha();
}

void Mario::actualizarPosicion(){
	this->movimiento->actualizarVelocidad();
	this->movimiento->aplicarCoeficienteDeRozamiento();
	float desplazamientoX = this->movimiento->calcularDesplazamientoHorizontal(0.016);
	this->posicion->moverHorizontal(desplazamientoX);

	float desplazamientoY = this->movimiento->calcularDesplazamientoVertical(0.1);

	if(this->posicion->obtenerPosY() + desplazamientoY < COORDENADA_Y_DEFAULT){
		this->posicion->moverVertical(COORDENADA_Y_DEFAULT - this->posicion->obtenerPosY());
		this->movimiento->setVelocidadY(0);
	}else{
		this->posicion->moverVertical(desplazamientoY);
	}
	this->movimiento->aplicarGravedad();

}
void Mario::saltar(){
	this->movimiento->saltar();
}

Mario::~Mario(){
	delete this->posicion;
	delete this->movimiento;
}
