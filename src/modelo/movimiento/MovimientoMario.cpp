#include "MovimientoMario.h"

const float MAXIMA_VELOCIDAD_X = 8;
const float ACELERACION_X = 0.8;
const float FUERZA_SALTO = 60;
MovimientoMario::MovimientoMario(){
	this->movimientoX = new MovimientoHorizontal(MAXIMA_VELOCIDAD_X, ACELERACION_X);
	this->movimientoY = new MovimientoVertical(FUERZA_SALTO);
	this->terrenoActual = new Tierra();
}

void MovimientoMario::aceleraraDerecha(){
	this->movimientoX->aceleraraDerecha(this->terrenoActual);
}

void MovimientoMario::aceleraraIzquierda(){
	this->movimientoX->aceleraraIzquierda(this->terrenoActual);
}

void MovimientoMario::saltar(){
	this->movimientoY->saltar(this->terrenoActual);
	delete terrenoActual;
	terrenoActual = new Aire();
}


void MovimientoMario::mover(PosicionMovil* posicion){

	this->movimientoX->mover(posicion, terrenoActual);

	int previoY = posicion->obtenerPosY();
	this->movimientoY->mover(posicion);
	if(posicion->obtenerPosY() == 0 && previoY > 0){
		delete terrenoActual;
		terrenoActual = new Tierra();
	}
}

bool MovimientoMario::estaQuieto(){
	return this->movimientoX->estaQuieto();
}

MovimientoMario::~MovimientoMario(){
	delete movimientoX;
	delete movimientoY;
	delete terrenoActual;
}
