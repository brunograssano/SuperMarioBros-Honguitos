#include "Colisionable.hpp"

void Colisionable::chocarPorDerechaCon(Colisionable *colisionable) {
    ejecutarFuncionDeColision(mapaColisionesPorDerecha, colisionable);
}

void Colisionable::chocarPorIzquierdaCon(Colisionable *colisionable) {
    ejecutarFuncionDeColision(mapaColisionesPorIzquierda, colisionable);
}

void Colisionable::chocarPorArribaCon(Colisionable *colisionable) {
    ejecutarFuncionDeColision(mapaColisionesPorArriba, colisionable);
}

void Colisionable::chocarPorAbajoCon(Colisionable *colisionable) {
    ejecutarFuncionDeColision(mapaColisionesPorAbajo, colisionable);
}

void Colisionable::ejecutarFuncionDeColision(std::map<std::string, parFuncionColisionContexto_t> mapaColisiones, Colisionable* colisionable) {
    parFuncionColisionContexto_t parFuncionColisionContexto = mapaColisiones[colisionable->obtenerColisionID()];
    if (parFuncionColisionContexto.funcion){
        (this->*parFuncionColisionContexto.funcion)(parFuncionColisionContexto.contexto);
    }
}


