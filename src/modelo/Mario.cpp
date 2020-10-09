#include "Mario.h"



Mario::Mario(){
	this->posicionX = 0;
	this->puntos=0;
}


void Mario::mover(Movimiento* unMovimiento){
	posicionX=unMovimiento->mover(posicionX);


}

int Mario::obtenerPosicion(){
	return posicionX;
}


Mario::~Mario(){
}

