#include "MovimientoMario.hpp"

const float MAXIMA_VELOCIDAD_X = 5;
const float ACELERACION_X = 0.3;
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
	if(posicion->obtenerPosY() == 0 && previoY > 0){ //Me fijo si estoy en tierra y si antes estaba en aire.
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
