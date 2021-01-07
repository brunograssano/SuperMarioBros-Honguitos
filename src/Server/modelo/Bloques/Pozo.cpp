#include "Pozo.hpp"
const int ANCHO_POZO = 50, ALTO_POZO = 0;


Pozo::Pozo(int posX, int tipo) {
    //TODO conseguir mejor forma de manejar esto, por ejemplo usar bloques de pozos con cada parte
    this->posicionX =  posX;
    this->tipo = tipo;
    dimensiones.x = posX;
    dimensiones.y = ALTO_POZO;
    dimensiones.h = ALTO_POZO;
    dimensiones.w = ANCHO_POZO;
}

bool Pozo::colisionaCon(Pozo* otroPozo) {
    unsigned short posXOtroPozo = otroPozo->obtenerPosicionX();
    SDL_Rect dimensionesOtroPozo = otroPozo->obtenerDimensiones();
    dimensionesOtroPozo.x += posXOtroPozo;
    dimensionesOtroPozo.w += posXOtroPozo;
    return SDL_HasIntersection(&dimensiones,&dimensionesOtroPozo);
}

unsigned short Pozo::obtenerPosicionX() const {
    return posicionX;
}

SDL_Rect Pozo::obtenerDimensiones() {
    return dimensiones;
}

pozo_t Pozo::serializar(){
    return {posicionX,tipo};
}