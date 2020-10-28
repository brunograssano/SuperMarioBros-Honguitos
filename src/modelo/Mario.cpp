#include "Mario.h"
#include "../log/Log.h"
#include <cmath>

const int COORDENADA_X_DEFAULT = 20;
const int COORDENADA_Y_DEFAULT = 0;
const int MINIMO_COORDENADA_Y = 0;
const int TERRENO_LIMITE_DERECHO_MAX = 8177;
const int TERRENO_LIMITE_DERECHO_MIN = 0;

Mario::Mario(){
	this->posicion = new PosicionMovil(COORDENADA_X_DEFAULT,COORDENADA_Y_DEFAULT, MINIMO_COORDENADA_Y,
			TERRENO_LIMITE_DERECHO_MIN, TERRENO_LIMITE_DERECHO_MAX);
	this->puntos=0;
	this->cantidadMonedas = 0;
	this->movimiento = new MovimientoMario();
	this->spriteMario = new SpriteMario("../resources/mario_grande.png");
}

SpriteMario* Mario::obtenerSpite(){
	return spriteMario;
}

void Mario::actualizarSaltarMario(){
	spriteMario->actualizarSpriteMarioSaltar(this);
}

void Mario::actualizarAgacharseMario(){
	spriteMario->actualizarSpriteMarioAgacharse(this);
}

void Mario::actualizarIzquierdaMario(){
	spriteMario->actualizarSpriteMarioIzquierda(this);
}

void Mario::actualizarDerechaMario(){
	spriteMario->actualizarSpriteMarioDerecha(this);
}




void Mario::actualizarMaximoX(int limite){
    this->posicion->actualizarLimiteTerrenoIzq(limite);
}

void Mario::actualizarMinimoX(int limite){
    this->posicion->actualizarLimiteTerrenoDer(limite);
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

void Mario::reiniciarPosicion(){
	delete posicion;
	delete movimiento;
	movimiento = new MovimientoMario();
	posicion = new PosicionMovil(COORDENADA_X_DEFAULT,COORDENADA_Y_DEFAULT, MINIMO_COORDENADA_Y,
			TERRENO_LIMITE_DERECHO_MIN, TERRENO_LIMITE_DERECHO_MAX);
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
	}
	spriteMario->actualizarSprite(this);
	Log::getInstance()->mostrarPosicion("Mario", posicion->obtenerPosX(), posicion->obtenerPosY());
}

void Mario::saltar(){
	this->movimiento->saltar();
}

bool Mario::estaQuietoX(){
	return this->movimiento->estaQuieto();
}

bool Mario::estaEnElPiso(){
	return this->posicion->obtenerPosY() == MINIMO_COORDENADA_Y;
}

Mario::~Mario(){
	delete this->spriteMario;
	delete this->posicion;
	delete this->movimiento;
}
