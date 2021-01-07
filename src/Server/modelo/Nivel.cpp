#include "Nivel.hpp"

#include <string>

#include "../../Utils/log/Log.hpp"

const int TAMANIO_MONEDA = 40;
const int TAMANIO_BLOQUE = 40;
const int TAMANIO_ENEMIGO = 40;

void Nivel::actualizarPosicionesEnemigos(){
	Log* log = Log::getInstance();
	int i = 1;
	for (auto const& enemigo : enemigos) {
	    enemigo->actualizarPosicion();
	    log->mostrarPosicion("Enemigo " + to_string(i), enemigo->obtenerPosicionX(), enemigo->obtenerPosicionY());
	    i++;
	}
}

void Nivel::actualizarMonedas(){
	for(auto const& moneda : monedas){
		moneda->actualizar();
	}
}

void Nivel::actualizarModelo(){
    //resolverColisiones();
    actualizarPosicionesEnemigos();
	actualizarMonedas();
}

string Nivel::obtenerDireccionFondoActual(){
	return direccionFondo;
}

float Nivel::obtenerPuntoBanderaFin() const{
	return puntoBanderaFin;
}

bool Nivel::esUnaPosicionXValidaEnemigo(int numeroPosicion){
	return !posicionesOcupadasXEnemigos[numeroPosicion];
}

bool Nivel::esUnaPosicionValidaMoneda(int numeroPosicionX, int numeroPosicionY){
	return !posicionesOcupadas[make_tuple(numeroPosicionX, numeroPosicionY)];
}

void Nivel::inicializar() {
    inicializarPosicionesOcupadasPorBloques();
    inicializarPosicionMonedas();
    inicializarPosicionEnemigo();
}

void Nivel::inicializarPosicionesOcupadasPorBloques(){

	for(auto const& plataforma : plataformas){
		list<Bloque*> bloques = plataforma->obtenerBloques();

		for(auto const& bloque : bloques){
			if((bloque->obtenerPosicionX() >= (int) puntoBanderaFin) || (bloque->obtenerPosicionY() >= ALTO_NIVEL)){
				Log::getInstance()->huboUnError("No se pudo poner un bloque en la posicion X: " + to_string(bloque->obtenerPosicionX()) +
						+ " Y: "+to_string(bloque->obtenerPosicionX()) +	" se pone en la posicion default");
				bloque->ubicarEnPosicionDefault();
			}

			posicionesOcupadas[make_tuple(bloque->obtenerPosicionX()/TAMANIO_BLOQUE, bloque->obtenerPosicionY()/TAMANIO_BLOQUE)] = true;
		}

	}
}

//rand() % (MAXIMO + 1 - MINIMO) + MINIMO

void Nivel::inicializarPosicionMonedas(){

	srand(time(nullptr));

	int cantidadMaximaMonedas = (int)(puntoBanderaFin/2)/(TAMANIO_MONEDA);

	if(cantidadMonedas > cantidadMaximaMonedas){
		Log::getInstance()->huboUnError("No se pueden poner " + to_string(cantidadMonedas) +" monedas, se ponen entonces: " + to_string(cantidadMaximaMonedas));
	}

	int numeroPosicionX = 0, numeroPosicionY = 0, coordenadaX = 0, coordenadaY = 0;

	int limiteXSuperior = (int)puntoBanderaFin;
	int limiteXInferior = (int)puntoBanderaFin/10;
	int limiteYInferior = ALTO_NIVEL/4;
	int limiteYSuperior = ALTO_NIVEL*1/2;

	for(int i=0; i<cantidadMonedas && i<cantidadMaximaMonedas; i++){

		do{
			numeroPosicionX = rand() % (limiteXSuperior/TAMANIO_MONEDA + 1 - limiteXInferior/TAMANIO_MONEDA) + limiteXInferior/TAMANIO_MONEDA;
			numeroPosicionY = rand() % (limiteYSuperior/TAMANIO_MONEDA + 1 - limiteYInferior/TAMANIO_MONEDA) + limiteYInferior/TAMANIO_MONEDA;
		}while(!this->esUnaPosicionValidaMoneda(numeroPosicionX, numeroPosicionY));

		this->posicionesOcupadas[make_tuple(numeroPosicionX, numeroPosicionY)] = true;

		coordenadaX = numeroPosicionX*TAMANIO_MONEDA;
		coordenadaY = numeroPosicionY*TAMANIO_MONEDA;

		this->agregarMoneda(new Moneda(coordenadaX, coordenadaY));

	}

}


void Nivel::inicializarPosicionEnemigo(){

	srand(time(nullptr));

	int numeroPosicionX = 0;

	int limiteXSuperior = (int)puntoBanderaFin;
	int limiteXInferior = (int)puntoBanderaFin/10;

	int coordenadaX = 0;
	int coordenadaY = 50;

	unsigned int cantidadMaximaEnemigos =  (unsigned int)(puntoBanderaFin/3)/TAMANIO_ENEMIGO;

	if(enemigos.size()>=cantidadMaximaEnemigos){
			Log::getInstance()->huboUnError("No se pudieron cargar "+ to_string((int)enemigos.size()) +
				" enemigos, se carga la cantidad maxima permitida para este nivel: " + to_string((int)cantidadMaximaEnemigos));
			auto iterador1 = enemigos.begin();
			auto iterador2 = enemigos.end();
			advance(iterador1, cantidadMaximaEnemigos-1);
			enemigos.erase(iterador1,iterador2);
	}

	for (auto const& enemigo : enemigos) {
		do{
			numeroPosicionX = rand() % (limiteXSuperior/TAMANIO_ENEMIGO + 1 - limiteXInferior/TAMANIO_ENEMIGO) + limiteXInferior/TAMANIO_ENEMIGO;
		}while(!esUnaPosicionXValidaEnemigo(numeroPosicionX));

		posicionesOcupadasXEnemigos[numeroPosicionX] = true;

		coordenadaX = numeroPosicionX*TAMANIO_ENEMIGO;
		enemigo->agregarPosicion(coordenadaX,coordenadaY);
	}

}

void Nivel::agregarTuberia(int posicionXNuevaTuberia, int tipoTuberia, int colorTuberia) {
    auto* posibleTuberia = new Tuberia(posicionXNuevaTuberia,tipoTuberia,colorTuberia);

    bool superponeAObjeto = false;
    for (auto tuberia:tuberias){ // llevar a otra funcion a parte la verificacion de superposicion
        if(tuberia->colisionaCon(posibleTuberia)){
            superponeAObjeto = true;
        }
    }
    // mismo chequeo para plataformas? <<< Debería

    if(!superponeAObjeto){
        tuberias.push_back(posibleTuberia);
    }
    else{
        delete posibleTuberia;
    }

}

void Nivel::completarInformacionRonda(info_ronda_t *ptrInfoRonda, bool (* deboAgregarlo)(void*, int), void* ctx) {
    if(!ptrInfoRonda) return;

    ptrInfoRonda->mundo = mundo;
    ptrInfoRonda->tiempoFaltante = contador->tiempoRestante();

    int numeroBloque = 0;
    for(auto const& plataforma: plataformas){
        list<bloque_t> bloques = plataforma->serializarPlataforma();

        for(auto const& bloque: bloques){
            if(deboAgregarlo(ctx, bloque.posX) &&
               numeroBloque<MAX_BLOQUES){
                ptrInfoRonda->bloques[numeroBloque] = bloque;
                numeroBloque++;
            }
        }
    }
    ptrInfoRonda->topeBloques = numeroBloque;

    int numeroEnemigo = 0;
    for(auto const& enemigo: enemigos){
        if(deboAgregarlo(ctx, enemigo->obtenerPosicionX()) &&
           numeroEnemigo<MAX_ENEMIGOS){
            ptrInfoRonda->enemigos[numeroEnemigo] = enemigo->serializar();
            numeroEnemigo++;
        }
    }
    ptrInfoRonda->topeEnemigos = numeroEnemigo;

    int numeroMoneda = 0;
    for(auto const& moneda: monedas){
        if(deboAgregarlo(ctx, moneda->obtenerPosicionX()) &&
           numeroMoneda<MAX_MONEDAS){
            ptrInfoRonda->monedas[numeroMoneda] = moneda->serializar();
            numeroMoneda++;
        }
    }
    ptrInfoRonda->topeMonedas = numeroMoneda;

    int numeroTuberia = 0;
    for(auto const& tuberia: tuberias){
        if(deboAgregarlo(ctx, tuberia->obtenerPosicionX()) &&
           numeroTuberia<MAX_TUBERIAS){
            ptrInfoRonda->tuberias[numeroTuberia] = tuberia->serializar();
            numeroTuberia++;
        }
    }
    ptrInfoRonda->topeTuberias = numeroTuberia;
}
