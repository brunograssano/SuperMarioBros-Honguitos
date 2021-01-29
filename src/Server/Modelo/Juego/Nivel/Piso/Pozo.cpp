#include "Pozo.hpp"
#include "src/Utils/Constantes.hpp"

Pozo::Pozo(int posicionX, int tipo, int fondo) {
    this->posicionX =  posicionX;
    this->tipo = tipo;
    this->fondo = fondo;
}

unsigned short Pozo::obtenerPosicionX() const {
    return posicionX;
}

entidad_t Pozo::serializar() const{
    entidad_t pozoSerializado = {0,0,0,0,0,false};
    pozoSerializado.x = posicionX;
    pozoSerializado.recorteX = fondo;
    pozoSerializado.recorteY = tipo; // Los tipos pinches, agua lava son de la misma imagen (recorte)
    pozoSerializado.tipo = POZO;
    return pozoSerializado;
}