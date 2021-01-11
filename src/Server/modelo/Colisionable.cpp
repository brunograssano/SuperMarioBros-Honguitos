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

void Colisionable::ejecutarFuncionDeColision(map<std::string, Colisionable::FuncionDeColision> mapaColisiones, Colisionable* colisionable) {
    Colisionable::FuncionDeColision funcionDeColision = mapaColisiones[colisionable->obtenerColisionID()];
    if(funcionDeColision){
        (this->*funcionDeColision)();
    }
}


