#include "Mario.h"

const int COORDENADA_X_DEFAULT = 20;
const int COORDENADA_Y_DEFAULT = 20;

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

Mario::~Mario(){
	delete this->posicion;
}

