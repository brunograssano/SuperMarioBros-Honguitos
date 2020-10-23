#include "MovimientoMario.h"

MovimientoMario::MovimientoMario(){
	this->movimientoX = new MovimientoHorizontalMario();
	this->movimientoY = new MovimientoVerticalMario();
}

void MovimientoMario::aceleraraDerecha(){
	this->movimientoX->aceleraraDerecha();
}

void MovimientoMario::aceleraraIzquierda(){
	this->movimientoX->aceleraraIzquierda();
}

void MovimientoMario::saltar(){
	this->movimientoY->saltar();
}


void MovimientoMario::mover(PosicionMovil* posicion){
	this->movimientoX->mover(posicion);
	this->movimientoY->mover(posicion);
}

bool MovimientoMario::estaQuieto(){
	return this->movimientoX->estaQuieto();
}
