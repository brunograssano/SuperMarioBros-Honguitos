#include "Serializador.hpp"

void Serializador::serializar(std::list<Bloque *> plataformas, info_ronda_t *ptrInfoRonda,bool (* deboAgregarlo)(void*, rectangulo_t), void* contexto) {
    int numeroBloque = 0;
    for(auto const& bloque: plataformas){
        if(bloque->cambioElSprite() && deboAgregarlo(contexto, bloque->obtenerRectangulo()) && numeroBloque < MAX_SORPRESAS){
            ptrInfoRonda->bloques[numeroBloque] = bloque->serializar();
            numeroBloque++;
        }
    }
    ptrInfoRonda->topeBloques = numeroBloque;
}

void Serializador::serializar(std::list<Enemigo *> enemigos, info_ronda_t *ptrInfoRonda,bool (*deboAgregarlo)(void *, rectangulo_t), void *contexto) {
    int numeroEnemigo = 0;
    for(auto const& enemigo: enemigos){
        if(deboAgregarlo(contexto, enemigo->obtenerRectangulo()) && numeroEnemigo<MAX_ENEMIGOS){
            ptrInfoRonda->enemigos[numeroEnemigo] = enemigo->serializar();
            numeroEnemigo++;
        }
    }
    ptrInfoRonda->topeEnemigos = numeroEnemigo;
}

void Serializador::serializar(std::list<Moneda *> monedas, info_ronda_t *ptrInfoRonda,bool (*deboAgregarlo)(void *, rectangulo_t), void *contexto) {
    int numeroMoneda = 0;
    for(auto const& moneda: monedas){
        if(deboAgregarlo(contexto, moneda->obtenerRectangulo()) && numeroMoneda<MAX_MONEDAS){
            ptrInfoRonda->monedas[numeroMoneda] = moneda->serializar();
            numeroMoneda++;
        }
    }
    ptrInfoRonda->topeMonedas = numeroMoneda;
}

void Serializador::serializar(std::list<ObjetoFugaz *> objetosFugaces, info_ronda_t *ptrInfoRonda,bool (*deboAgregarlo)(void *, rectangulo_t), void *contexto) {
    int numeroEfecto = 0;
    for(auto const& objeto : objetosFugaces){
        if(deboAgregarlo(contexto, objeto->obtenerRectangulo()) && numeroEfecto<MAX_EFECTOS){
            ptrInfoRonda->efectos[numeroEfecto] = objeto->serializar();
            numeroEfecto++;
        }
    }
    ptrInfoRonda->topeEfectos = numeroEfecto;
}

void Serializador::serializar(std::list<Tuberia *> tuberias, nivel_t *nivel) {
    for(auto const& tuberia: tuberias){
        if(nivel->topeTuberias<MAX_TUBERIAS){
            nivel->tuberias[nivel->topeTuberias] = tuberia->serializar();
            nivel->topeTuberias++;
        }
    }
}

void Serializador::serializar(std::list<Bloque *> plataformas, nivel_t *nivel) {
    for(auto const& bloque: plataformas){
        entidad_t  bloquesSerializado = bloque->serializar();
        if(nivel->topeBloques<MAX_LADRILLOS && bloquesSerializado.recorteY!=SORPRESA){
            nivel->bloques[nivel->topeBloques] = bloquesSerializado;
            nivel->topeBloques++;
        }
    }
}

void Serializador::serializar(std::list<entidad_t> pozos, nivel_t *nivel) {
    for(auto const& pozo: pozos){
        if(nivel->topePozos<MAX_POZOS){
            nivel->pozos[nivel->topePozos] = pozo;
            nivel->topePozos++;
        }
    }
}
