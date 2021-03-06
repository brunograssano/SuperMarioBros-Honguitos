#include "Sorpresa.hpp"
#include "ObjetosSorpresa/FlorDeFuego.hpp"
#include "ObjetosSorpresa/MonedaSorpresa.hpp"

#include "src/Server/Modelo/Juego/Sprites/SpriteSorpresa.hpp"

#define PROBABILIDAD_NECESARIA_PARA_FLOR 80

Sorpresa::Sorpresa(int coordenadaX, int coordenadaY) {
    tipoBloque = SORPRESA;
    int coordenadaXNormalizada = normalizarCoordenadaIngresada(coordenadaX);
    int coordenadaYNormalizada = normalizarCoordenadaIngresada(coordenadaY);
    this->posicion = PosicionFija(coordenadaXNormalizada, coordenadaYNormalizada);
    this->spriteBloque = new SpriteSorpresa();
    this->objetoSorpresa = obtenerObjetoSorpresa(posicion.obtenerPosX(), posicion.obtenerPosY() + LARGO_BLOQUE);
    usado = false;
    entregado = false;
    Sorpresa::inicializarMapasDeColision();
}

void Sorpresa::inicializarMapasDeColision(){
    auto pUsarse = (void (Colisionable::*)(void*)) &Sorpresa::usarse;
    Colisionable::parFuncionColisionContexto_t parUsarse = {pUsarse, nullptr};

    mapaColisionesPorAbajo[COLISION_ID_MARIO] = parUsarse;
}

ObjetoSorpresa* Sorpresa::obtenerObjetoSorpresa(int posX, int posY) {
    ObjetoSorpresa* objeto;
    unsigned int probabilidad = rand()%101;
    if(probabilidad > PROBABILIDAD_NECESARIA_PARA_FLOR){
        objeto = new FlorDeFuego(posX,posY);
    }
    else{
        PosicionFija pos(posX, posY);
        objeto = new MonedaSorpresa(&pos);
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

std::string Sorpresa::obtenerColisionID() {
    return COLISION_ID_SORPRESA;
}

Sorpresa::~Sorpresa() {
    delete this->spriteBloque;
    if(!usado){
        delete this->objetoSorpresa;
    }
}

void Sorpresa::elevar(int y) {
    Bloque::elevar(y);
    delete objetoSorpresa;
    objetoSorpresa = obtenerObjetoSorpresa(posicion.obtenerPosX(), posicion.obtenerPosY() + LARGO_BLOQUE);
}

void Sorpresa::usarse(__attribute__((unused))void* pVoid) {
    spriteBloque->usarse();
    usado = true;
    if(!entregado){
        objetoSorpresa->sonar();
    }
}
