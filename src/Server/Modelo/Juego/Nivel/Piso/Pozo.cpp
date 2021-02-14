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

entidad_t Pozo::serializar(){
    return Serializable::serializar(posicionX,0,fondo,tipo,POZO, false);
}