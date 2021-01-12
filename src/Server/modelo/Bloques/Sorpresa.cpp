#include "Sorpresa.hpp"
#include "ObjetosSorpresa/FlorDeFuego.h"
#include "ObjetosSorpresa/MonedaSorpresa.hpp"

Sorpresa::Sorpresa(int coordenadaX, int coordenadaY) {
    tipoBloque = SORPRESA;
    int coordenadaXNormalizada = normalizarCoordenadaIngresada(coordenadaX);
    int coordenadaYNormalizada = normalizarCoordenadaIngresada(coordenadaY);
    this->posicion = new PosicionFija(coordenadaXNormalizada, coordenadaYNormalizada);
    this->spriteBloque = new SpriteSorpresa(false);
    SDL_Rect rectangulo = spriteBloque->obtenerRectanguloActual();
    this->objetoSorpresa = obtenerObjetoSorpresa(posicion->obtenerPosX(), posicion->obtenerPosY() + rectangulo.h);
    usado = false;
    entregado = false;
    inicializarMapasDeColision();
}

void Sorpresa::inicializarMapasDeColision(){}

ObjetoSorpresa* Sorpresa::obtenerObjetoSorpresa(int posX, int posY) {
    ObjetoSorpresa* objeto;
    if(rand()%2 == 0){
        objeto = new FlorDeFuego(posX,posY);
    }
    else{
        objeto = new MonedaSorpresa();
    }
    return objeto;
}

ObjetoSorpresa* Sorpresa::colisionaronAbajo() {
    if(usado && !entregado){
        entregado = true;
        return objetoSorpresa;
    }
    return new SinSorpresa();
}

string Sorpresa::obtenerColisionID() {
    return COLISION_ID_SORPRESA;
}

void Sorpresa::chocarPorAbajoCon(Colisionable *colisionable) {
    delete spriteBloque;
    spriteBloque = new SpriteSorpresa(true);
    usado = true;
}

Sorpresa::~Sorpresa() {
    delete this->posicion;
    delete this->spriteBloque;
    delete this->objetoSorpresa;
}
