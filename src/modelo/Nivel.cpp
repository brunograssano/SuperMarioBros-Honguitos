
#include <string>
#include "Nivel.h"
#include "../log/Log.h"


void Nivel::actualizarPosicionesEnemigos(){
	Log* log = Log::getInstance();
	int i = 1;
	for (auto const& enemigo : enemigos) {
	    enemigo->actualizarPosicion();
	    log->mostrarPosicion("Enemigo " + to_string(i), enemigo->obtenerPosicionX(), enemigo->obtenerPosicionY());
	    i++;
	}
}

list<Enemigo*> Nivel::obtenerEnemigos(){
	return enemigos;
}
list<Plataforma*> Nivel::obtenerPlataformas(){
	return plataformas;
}

list<Moneda*> Nivel::obtenerMonedas(){
	return monedas;
}

string Nivel::obtenerDireccionFondoActual(){
	return direccionFondo;
}

bool Nivel::esUnaPosicionXValidaEnemigo(int numeroPosicion){
	return !posicionesOcupadasXEnemigos[numeroPosicion];
}

bool Nivel::esUnaPosicionValidaMoneda(int numeroPosicionX, int numeroPosicionY){
	return !posicionesOcupadas[make_tuple(numeroPosicionX, numeroPosicionY)];
}

void Nivel::inicializarPosicionesOcupadasPorBloques(){

	list<Plataforma*> plataformas = this->obtenerPlataformas();
	for(auto const& plataforma : plataformas){

		list<Bloque*> bloques = plataforma->obtenerBloques();

		for(auto const& bloque : bloques){
			posicionesOcupadas[make_tuple(bloque->obtenerPosicionX()/40, bloque->obtenerPosicionY()/40)] = true;
		}
	}
}

void Nivel::inicializarPosicionMonedas(){

	srand(time(NULL));

	int numeroPosicionX = 0, numeroPosicionY = 0, coordenadaX = 0, coordenadaY = 0;

	int limiteXSuperior = puntoBanderaFin;
	int limiteYInferior = altoNivel*1/4;
	int anchoY = altoNivel*3/4;


	for(int i=0; i<cantidadMonedas; i++){

		do{
			numeroPosicionX = rand() % (limiteXSuperior/40);
			numeroPosicionY = rand() % (anchoY/40) + (limiteYInferior/40);
		}while(!this->esUnaPosicionValidaMoneda(numeroPosicionX, numeroPosicionY));

		this->posicionesOcupadas[make_tuple(numeroPosicionX, numeroPosicionY)] = true;

		coordenadaX = numeroPosicionX*40;
		coordenadaY = numeroPosicionY*40;

		this->agregarMoneda(new Moneda(coordenadaX, coordenadaY));

	}

}


void Nivel::inicializarPosicionEnemigo(){

	srand(time(NULL));

	int numeroPosicion = 0;
	int coordenadaX = 0;

	for (auto const& enemigo : enemigos) {

		do{
			numeroPosicion = rand()%(puntoBanderaFin/40);
		}while(!esUnaPosicionXValidaEnemigo(numeroPosicion));

		posicionesOcupadasXEnemigos[numeroPosicion] = true;
		coordenadaX = numeroPosicion*40;
		enemigo->agregarPosicion(coordenadaX,50);
	}

}
