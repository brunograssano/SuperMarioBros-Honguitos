#include "Bloque.hpp"


int Bloque::obtenerPosicionX() {
    return this->posicion.obtenerPosX();
}

int Bloque::obtenerPosicionY() {
    return this->posicion.obtenerPosY();
}

ObjetoSorpresa* Bloque::colisionaronAbajo() {
    return new SinSorpresa();
}

int Bloque::normalizarCoordenadaIngresada(int coordenada) {
    return (coordenada/40)*40;
}

entidad_t Bloque::serializar() {
    return Serializable::serializar(posicion.obtenerPosX(),posicion.obtenerPosY(),spriteBloque->obtenerEstadoActual(),tipoBloque,BLOQUE,false);
}

rectangulo_t Bloque::obtenerRectangulo() {
    int x = posicion.obtenerPosX();
    int y = posicion.obtenerPosY();
    int h = LARGO_BLOQUE;
    int w = LARGO_BLOQUE;
    return {x,x+w,y,y+h,h,w};
}

bool Bloque::cambioElSprite() {
    return spriteBloque->cambioElSprite();
}

bool Bloque::debeColisionar() {
    return true;
}

void Bloque::actualizar() {
    spriteBloque->actualizarSprite();
}

void Bloque::elevar(int y) {
    int yAnt = posicion.obtenerPosY();
    int xAnt = posicion.obtenerPosX();
    posicion = PosicionFija(xAnt, yAnt + y);
}
