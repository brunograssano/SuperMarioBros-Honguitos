#include "Nivel.hpp"

#include <string>

const int TAMANIO_MONEDA = 40;
const int TAMANIO_BLOQUE = 40;
const int TAMANIO_ENEMIGO = 40;

Nivel::Nivel(int mundo, string direccionFondo, int tiempo, int cantidadMonedas, int puntoBanderaFin) {
    this->mundo = mundo;
    this->direccionFondo = std::move(direccionFondo);
    this->tiempo = tiempo;
    this->cantidadMonedas = cantidadMonedas;
    this->puntoBanderaFin = ANCHO_FONDO2* (float) puntoBanderaFin /100;
    this->contador = new Contador(tiempo, SEGUNDOS);
    this->meta = new Meta(this->puntoBanderaFin);
}

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

void Nivel::actualizarModelo(map<int, Mario*> jugadores){
    //resolverColisiones(jugadores);
    actualizarPosicionesEnemigos();
    actualizarMonedas();
    resolverGanadores(jugadores);
}

void Nivel::resolverGanadores(map<int, Mario *> mapaJugadores) {
    for(auto const& parClaveJugador:mapaJugadores)
        meta->agregarSiPasoLaMeta(parClaveJugador.second);
}

void Nivel::sacarEnemigosMuertos(){
    list<Enemigo*> enemigosABorrar;
    for(auto enemigo : enemigosMuertos){ // se moverian a la lista esta una vez que detectamos colision por arriba
        if(enemigo->sePuedeEliminar()){ // la otra opcion es mantenerlos en la lista original, e ir verificando si estan muertos
            enemigosABorrar.push_back(enemigo);
        }
    }
    for(auto enemigo : enemigosABorrar ){
        enemigosMuertos.remove(enemigo);
        delete enemigo;
    }
}

string Nivel::obtenerDireccionFondoActual(){
	return direccionFondo;
}

int Nivel::obtenerMundo() const{
    return mundo;
}

void Nivel::agregarPlataforma(Plataforma* unaPlataforma){
    plataformas.push_back(unaPlataforma);
}
void Nivel::agregarEnemigo(Enemigo* unEnemigo){
    enemigos.push_back(unEnemigo);
}
void Nivel::agregarMoneda(Moneda* unaMoneda){
    monedas.push_back(unaMoneda);
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

void Nivel::agregarPozo(int posicionXNuevoPozo, int tipoPozo) {
    auto* posiblePozo = new Pozo(posicionXNuevoPozo, tipoPozo);

    bool superponeAObjeto = false;
    for (auto pozo:pozos){ // llevar a otra funcion a parte la verificacion de superposicion
        if(pozo->colisionaCon(posiblePozo)){
            superponeAObjeto = true;
        }
    }
    // mismo chequeo para plataformas?
    if(!superponeAObjeto){
        pozos.push_back(posiblePozo);
    }
    else{
        delete posiblePozo;
    }
}

Nivel::~Nivel (){
    for(const auto& plataforma:plataformas){
        delete plataforma;
    }
    for(const auto& moneda:monedas){
        delete moneda;
     }
    for(const auto& enemigo:enemigos){
        delete enemigo;
    }
    plataformas.clear();
    enemigos.clear();
    monedas.clear();
    delete contador;
    delete meta;
}

void Nivel::terminar() {
    meta->sumarPuntos(contador->tiempoRestante());
}

bool Nivel::todosEnLaMeta(map<int, Mario *> jugadores) {
    return meta->todosEnLaMeta(jugadores);
}
