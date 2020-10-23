#include "MovimientoMario.h"



const float COEFICIENTE_DE_TIEMPO = 0.16;

MovimientoMario::MovimientoMario(){
	this->aceleracionY = 0;
	this->velocidadY = 0;
	this->movimientoX = new MovimientoHorizontalMario();
}

void MovimientoMario::aceleraraDerecha(){
	this->movimientoX->aceleraraDerecha();
}

void MovimientoMario::aceleraraIzquierda(){
	this->movimientoX->aceleraraIzquierda();
}

void MovimientoMario::saltar(){
	this->velocidadY = 60;
}


void MovimientoMario::aplicarGravedad(){
	this->velocidadY -= 9.8*COEFICIENTE_DE_TIEMPO;
}

void MovimientoMario::mover(PosicionMovil* posicion){
	this->movimientoX->mover(posicion);
	float desplazamientoY = this->velocidadY*COEFICIENTE_DE_TIEMPO;
	posicion->moverVertical(desplazamientoY);
	aplicarGravedad();
}

bool MovimientoMario::estaQuieto(){
	return this->movimientoX->estaQuieto();
}
