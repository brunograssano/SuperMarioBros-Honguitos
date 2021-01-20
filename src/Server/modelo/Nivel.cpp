#include "Nivel.hpp"
#include "src/Utils/colisiones/Colisionador.hpp"
#include <string>

#include "src/Server/modelo/Bloques/PiezaDeTuberia.hpp"

const int TAMANIO_MONEDA = 40;
const int TAMANIO_BLOQUE = 40;
const int TAMANIO_ENEMIGO = 40;

Nivel::Nivel(int mundo, string direccionFondo, int tiempo, int cantidadMonedas, int puntoBanderaFin, int altoPiso) {
    this->mundo = mundo;
    this->direccionFondo = std::move(direccionFondo);
    this->tiempo = tiempo;
    this->cantidadMonedas = cantidadMonedas;
    this->puntoBanderaFin = ANCHO_FONDO* (float) puntoBanderaFin /100;
    this->contador = Contador(tiempo, SEGUNDOS);
    this->meta = Meta(this->puntoBanderaFin);
    this->piso = Piso(altoPiso);
    this->podio = new Podio();
}

void Nivel::actualizarPosicionesEnemigos(rectangulo_t rectangulo) {
	Log* log = Log::getInstance();
	int i = 1;
	for (auto& enemigo : enemigos) {
        enemigo->actualizarPosicion(rectangulo);
	    log->mostrarPosicion("Enemigo " + to_string(i), enemigo->obtenerPosicionX(), enemigo->obtenerPosicionY());
	    i++;
	}
}

void Nivel::actualizarMonedas(){
	for(auto& moneda : monedas){
		moneda->actualizar();
	}
}

void Nivel::actualizarBloques() {
    for(auto& bloque : plataformas){
        bloque->actualizar();
    }
}

void Nivel::actualizarObjetosFugaces() {
    for(auto& objeto: objetosFugaces) {
        objeto->actualizar();
    }
}


void Nivel::actualizarModelo(map<int, Mario*> jugadores, rectangulo_t rectanguloEscena){
    actualizarPosicionesEnemigos(rectanguloEscena);

    imponerPosicionDeReaparicion(jugadores, rectanguloEscena);
    resolverColisiones(jugadores);

    actualizarObjetosFugaces();
    actualizarMonedas();
    actualizarBloques();

    sacarEnemigosMuertos();
    sacarObjetosFugaces();
    sacarMonedasAgarradas();

    resolverGanadores(jugadores);
}

void Nivel::resolverColisiones(map<int, Mario *> jugadores) {
    list<Colisionable*> plataformasPiso = piso.obtenerPiso();

    //todo: mejorar esto:
    list<PiezaDeTuberia*> piezasDeTuberia;
    for(auto& tuberia: tuberias){
        list<PiezaDeTuberia*> piezasTuberiaActual = tuberia->obtenerPiezas();
        piezasDeTuberia.insert(piezasDeTuberia.end(), piezasTuberiaActual.begin(), piezasTuberiaActual.end());
    }


    for(auto& parClaveJugador: jugadores){
        Mario* jugador = parClaveJugador.second;
        chocarContraTodos(jugador, (void*)&enemigos, nullptr, nullptr);
        chocarContraTodos(jugador, (void*)&monedas, nullptr, nullptr);
        chocarContraTodos(jugador, (void*)&plataformas,&Nivel::agregarObjeto_helper, this);
        chocarContraTodos(jugador, (void*)&objetosFugaces, nullptr, nullptr);
        chocarContraTodos(jugador,(void*) &plataformasPiso,nullptr, nullptr);
        chocarContraTodos(jugador, (void*) &piezasDeTuberia,nullptr, nullptr);
    }
    for(auto& enemigo:enemigos){
        chocarContraTodos(enemigo, (void*)&objetosFugaces, nullptr, nullptr);
        chocarContraTodos(enemigo, (void*)&plataformas, nullptr, nullptr);
        chocarContraTodos(enemigo,(void*)&plataformasPiso,nullptr, nullptr);
        chocarContraTodos(enemigo, (void*)&piezasDeTuberia,nullptr, nullptr);
    }
    for(auto& objeto: objetosFugaces){
        chocarContraTodos(objeto, (void*) &plataformasPiso, nullptr, nullptr);
        chocarContraTodos(objeto, (void*)&plataformas, nullptr, nullptr);
        chocarContraTodos(objeto, (void*) &piezasDeTuberia,nullptr, nullptr);
    }
}

void Nivel::resolverGanadores(map<int, Mario *> mapaJugadores) {
    for(auto const& parClaveJugador:mapaJugadores)
        meta.agregarSiPasoLaMeta(parClaveJugador.second);
}

void Nivel::sacarEnemigosMuertos(){
    list<Enemigo*> enemigosABorrar;
    for(auto enemigo : enemigos){
        if(enemigo->sePuedeEliminar()){
            enemigosABorrar.push_back(enemigo);
        }
    }
    for(auto enemigo : enemigosABorrar ){
        enemigos.remove(enemigo);
        delete enemigo;
    }
}
void Nivel::sacarMonedasAgarradas() {
    list<Moneda*> monedasABorrar;
    for(auto moneda : monedas){
        if(moneda->fueAgarrada()){
            monedasABorrar.push_back(moneda);
        }
    }
    for(auto moneda : monedasABorrar ){
        monedas.remove(moneda);
        delete moneda;
    }
}

void Nivel::sacarObjetosFugaces() {
    list<ObjetoFugaz*> objetosABorrar;
    for(auto const& objeto: objetosFugaces){
        if(objeto->debeDesaparecer()){
            objetosABorrar.push_back(objeto);
        }
    }
    for(auto objeto : objetosABorrar){
        objetosFugaces.remove(objeto);
        delete objeto;
    }
}


string Nivel::obtenerDireccionFondoActual(){
	return direccionFondo;
}

int Nivel::obtenerMundo() const{
    return mundo;
}

void Nivel::agregarPlataforma(list<Bloque *> unaPlataforma){
    plataformas.splice(plataformas.end(),unaPlataforma);
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
    inicializarPosicionOcupadasPorTuberias();
    inicializarPosicionMonedas();
    inicializarPosicionEnemigo();
    elevarObstaculos();
    piso.inicializar();
}

void Nivel::elevarObstaculos() {
    for(auto& bloque: plataformas){
        bloque->elevar(piso.obtenerAltura());
    }
    for(auto& tuberia: tuberias){
        tuberia->elevar(piso.obtenerAltura());
    }
    for(auto& moneda: monedas){
        moneda->elevar(piso.obtenerAltura());
    }
}

void Nivel::inicializarPosicionesOcupadasPorBloques(){

    list<Bloque *> plataformasARemover;
    for(auto const& bloque : plataformas){
        if((bloque->obtenerPosicionX() >= (int) puntoBanderaFin) || (bloque->obtenerPosicionY() >= ALTO_NIVEL)){
            Log::getInstance()->huboUnError("No se pudo poner un bloque en la posicion X: " + to_string(bloque->obtenerPosicionX()) +
                    + " Y: "+to_string(bloque->obtenerPosicionX()) +	" se elimina");
            plataformasARemover.push_back(bloque);
        }
        posicionesOcupadas[make_tuple(bloque->obtenerPosicionX()/TAMANIO_BLOQUE, bloque->obtenerPosicionY()/TAMANIO_BLOQUE)] = true;
    }

    for(auto const& bloque : plataformasARemover){
        this->plataformas.remove(bloque);
    }
}

void Nivel::inicializarPosicionOcupadasPorTuberias(){
    int posicionesQueOcupaUnaTuberia = 5;
    int posicionXOcupada;
    int posicionYOcupada;
    for(auto const& tuberia : tuberias){
        posicionXOcupada = tuberia->obtenerPosicionX()/TAMANIO_BLOQUE;
        posicionYOcupada = 0;
        for(int i = 0; i < posicionesQueOcupaUnaTuberia; i++) {
            for(int j = 0; j < posicionesQueOcupaUnaTuberia; j++){
                posicionesOcupadas[make_tuple(posicionXOcupada+i, posicionYOcupada+j)] = true;
            }
        }
    }
}

//rand() % (MAXIMO + 1 - MINIMO) + MINIMO

void Nivel::inicializarPosicionMonedas(){

	int cantidadMaximaMonedas = (int)(puntoBanderaFin/2)/(TAMANIO_MONEDA);

	if(cantidadMonedas > cantidadMaximaMonedas){
		Log::getInstance()->huboUnError("No se pueden poner " + to_string(cantidadMonedas) +" monedas, se ponen entonces: " + to_string(cantidadMaximaMonedas));
	}

	int numeroPosicionX = 0, numeroPosicionY = 0, coordenadaX = 0, coordenadaY = 0;

	int limiteXSuperior = (int)puntoBanderaFin;
	int limiteXInferior = (int)puntoBanderaFin/10;
	int limiteYInferior = ALTO_NIVEL/6;
	int limiteYSuperior = (ALTO_NIVEL*2)/5;

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

	int numeroPosicionX = 0;

	int limiteXSuperior = (int)puntoBanderaFin;
	int limiteXInferior = (int)puntoBanderaFin/10;

	int coordenadaX = 0;
	int coordenadaY = 100;

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

void Nivel::completarInformacionRonda(info_ronda_t *ptrInfoRonda, bool (* deboAgregarlo)(void*, rectangulo_t), void* contexto) {
    if(!ptrInfoRonda) return;

    ptrInfoRonda->tiempoFaltante = contador.tiempoRestante();

    int numeroBloque = 0;
    for(auto const& bloque: plataformas){
        bloque_t bloqueSerializado = bloque->serializar();
        if(bloque->cambioElSprite() && deboAgregarlo(contexto, bloque->obtenerRectangulo()) && numeroBloque < MAX_SORPRESAS){
            ptrInfoRonda->bloques[numeroBloque] = bloqueSerializado;
            numeroBloque++;
        }
    }
    ptrInfoRonda->topeBloques = numeroBloque;

    int numeroEnemigo = 0;
    for(auto const& enemigo: enemigos){
        if(deboAgregarlo(contexto, enemigo->obtenerRectangulo()) &&
           numeroEnemigo<MAX_ENEMIGOS){
            ptrInfoRonda->enemigos[numeroEnemigo] = enemigo->serializar();
            numeroEnemigo++;
        }
    }
    ptrInfoRonda->topeEnemigos = numeroEnemigo;

    int numeroMoneda = 0;
    for(auto const& moneda: monedas){
        if(deboAgregarlo(contexto, moneda->obtenerRectangulo()) &&
           numeroMoneda<MAX_MONEDAS){
            ptrInfoRonda->monedas[numeroMoneda] = moneda->serializar();
            numeroMoneda++;
        }
    }

    ptrInfoRonda->topeMonedas = numeroMoneda;
    int numeroEfecto = 0;
    for(auto const& disparo : objetosFugaces){
        if(deboAgregarlo(contexto, disparo->obtenerRectangulo()) &&
            numeroEfecto<MAX_EFECTOS){
            ptrInfoRonda->efectos[numeroEfecto] = disparo->serializar();
            numeroEfecto++;
        }
    }
    ptrInfoRonda->topeEfectos = numeroEfecto;
}

void Nivel::agregarPozo(int posicionX, int tipoPozo, int fondo) {
    piso.agregarPozo(posicionX, tipoPozo, fondo);
}

void Nivel::terminar(map<int, Mario *> jugadores) {
    meta.sumarPuntos(contador.tiempoRestante());

    for(auto const& parJugador:jugadores){
        parJugador.second->eliminar(podio);
    }
}

bool Nivel::todosEnLaMeta(map<int, Mario *> jugadores) {
    return meta.todosEnLaMeta(jugadores);
}

void Nivel::completarInformacionNivel(nivel_t *nivel) {
    nivel->mundo = mundo;
    for(auto const& tuberia: tuberias){
        if(nivel->topeTuberias<MAX_TUBERIAS){
            nivel->tuberias[nivel->topeTuberias] = tuberia->serializar();
            nivel->topeTuberias++;
        }
    }

    list<pozo_t> pozos = piso.serializar();
    for(auto const& pozo: pozos){
        if(nivel->topePozos<MAX_POZOS){
            nivel->pozos[nivel->topePozos] = pozo;
            nivel->topePozos++;
        }
    }

    for(auto const& bloque: plataformas){
        bloque_t  bloquesSerializado = bloque->serializar();
        if(nivel->topeBloques<MAX_LADRILLOS && bloquesSerializado.numeroRecorteY!=SORPRESA){
            nivel->bloques[nivel->topeBloques] = bloquesSerializado;
            nivel->topeBloques++;
        }
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
    for(const auto& disparo:objetosFugaces){
        delete disparo;
    }
    objetosFugaces.clear();
    plataformas.clear();
    enemigos.clear();
    monedas.clear();
    delete this->podio;
}

void Nivel::iniciar(map<int, Mario*> jugadores) {
    contador.iniciar();
    podio->recibirJugadores(jugadores);
    for(auto const& parJugador:jugadores){
        parJugador.second->agregar(podio);
    }
}

Podio* Nivel::obtenerPodio(){
    return this->podio;
}

int Nivel::tiempoRestante() {
    return contador.tiempoRestante();
}

void Nivel::aparecerDisparo(ObjetoFugaz* disparo) {
    objetosFugaces.push_back(disparo);
}

void Nivel::agregarObjeto_helper(void* ptr_jugador, void *ptr_bloque, void *ptr_nivel) {
    ((Nivel *) ptr_nivel)->utilizarSorpresa((Mario *) ptr_jugador, (Bloque *) ptr_bloque);
}

void Nivel::utilizarSorpresa(Mario* jugador, Bloque *bloque) {
    ObjetoSorpresa* objeto = bloque->colisionaronAbajo();
    objeto->usarse(jugador);
    if(objeto->debeDesaparecer()){
        delete objeto;
    }
    else{
        objetosFugaces.push_front(objeto);
    }
}


void Nivel::buscarBloqueParaCaer(rectangulo_t rectanguloEscena, PosicionFija* pos) {
    int xActual = rectanguloEscena.x1;
    int yActual = rectanguloEscena.y2;
    bool hayCandidato = false;

    for(auto const& bloque : plataformas){
        rectangulo_t rectBloque = bloque->obtenerRectangulo();
        rectangulo_t interseccion{};
        bool hayInterseccion = intersecarRectangulos(rectanguloEscena, rectBloque, &interseccion);
        if(hayInterseccion && interseccion.w >= ANCHO_MARIO){
            if(!hayCandidato){
                xActual = rectBloque.x1;
                yActual = rectBloque.y2;
                hayCandidato = true;
            }else if(rectBloque.x1 < xActual){
                xActual = rectBloque.x1;
                yActual = rectBloque.y2;
            }
        }
    }

    *pos = PosicionFija(xActual, yActual);
}


void Nivel::imponerPosicionDeReaparicion(map<int, Mario*> jugadores, rectangulo_t rectanguloEscena) {
    PosicionFija posicionDeReaparicion(rectanguloEscena.x1, piso.obtenerAltura());

    bool hayPiso = piso.obtenerRespawn(rectanguloEscena, &posicionDeReaparicion);
    if(!hayPiso) {
        buscarBloqueParaCaer(rectanguloEscena, &posicionDeReaparicion);
    }

    for(auto& parClaveJugador : jugadores){
        Mario* jugador = parClaveJugador.second;
        jugador->nuevoPuntoDeReaparicion(posicionDeReaparicion);
    }
}

