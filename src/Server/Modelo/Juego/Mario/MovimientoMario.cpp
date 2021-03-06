#include "MovimientoMario.hpp"

#include "src/Server/Modelo/Juego/Terrenos/CabezaEnemigo.hpp"
#include "src/Server/Modelo/Juego/Terrenos/Aire.hpp"
#include "src/Server/Modelo/Juego/Terrenos/Tierra.hpp"

const float MAXIMA_VELOCIDAD_X = 5;
const float ACELERACION_X = 0.3;
const float FUERZA_SALTO = 60;

const int TIERRA = 1, AIRE = 2, CABEZA_ENEMIGO = 3, BLOQUE = TIERRA;

MovimientoMario::MovimientoMario(){
	this->movimientoX = MovimientoHorizontal(MAXIMA_VELOCIDAD_X, ACELERACION_X);
	this->movimientoY = MovimientoVertical(FUERZA_SALTO);

	this->terrenos[TIERRA] = new Tierra();
	this->terrenos[AIRE] = new Aire();
	this->terrenos[CABEZA_ENEMIGO] = new CabezaEnemigo();
	terrenoActual = TIERRA;
}

void MovimientoMario::aceleraraDerecha(){
	this->movimientoX.aceleraraDerecha(terrenos[terrenoActual]);
}

void MovimientoMario::aceleraraIzquierda(){
	this->movimientoX.aceleraraIzquierda(terrenos[terrenoActual]);
}

void MovimientoMario::saltar(){
	this->movimientoY.saltar(terrenos[terrenoActual]);
	terrenoActual = AIRE;
}


void MovimientoMario::mover(PosicionMovil* posicion){
    this->movimientoX.mover(posicion, terrenos[terrenoActual]);
	this->movimientoY.mover(posicion);
	terrenoActual = AIRE;
}

bool MovimientoMario::estaQuieto(){
	return this->movimientoX.estaQuieto();
}

float MovimientoMario::obtenerVelocidadXActual() {
    return movimientoX.obtenerVelocidadXActual();
}

void MovimientoMario::impulsarY() {
    this->movimientoY.saltar(terrenos[CABEZA_ENEMIGO]);
    terrenoActual = AIRE;
}

void MovimientoMario::reiniciar() {
    setVelocidadY(0);
    this->movimientoX.setVelocidad(0);
    terrenoActual = AIRE;
}

void MovimientoMario::setVelocidadX(int velocidadNueva) {
    this->movimientoX.setVelocidad(velocidadNueva);
}

void MovimientoMario::setVelocidadY(int velocidad) {
    this->movimientoY.setVelocidadY(velocidad);
}

void MovimientoMario::teParasteEnBloque(){
    terrenoActual = BLOQUE;
}

bool MovimientoMario::estaEnElAire() const {
    return terrenoActual == AIRE;
}

MovimientoMario::~MovimientoMario(){
    for(auto parClaveTerreno:terrenos){
        delete parClaveTerreno.second;
    }
}