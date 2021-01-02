#include "Tuberia.hpp"

const int ANCHO_PRIMERA_TUBERIA = 33, ALTO_TUBERIA = 66,TUBERIA_PEQUENIA=0,ANCHO_SEGUNDA_TUBERIA = 67;

Tuberia::Tuberia(int posX, int tipo, int color) {
    //TODO conseguir mejor forma de manejar esto, por ejemplo usar bloques de tuberias con cada parte
    this->posicionX =  posX;
    this->tipo = tipo;
    this->color = color;
    dimensiones.x = tipo * ANCHO_PRIMERA_TUBERIA;
    dimensiones.y = color * ALTO_TUBERIA;
    dimensiones.h = ALTO_TUBERIA;

    if(tipo==TUBERIA_PEQUENIA){
        dimensiones.w = ANCHO_PRIMERA_TUBERIA;
    }
    else{
        dimensiones.w = ANCHO_SEGUNDA_TUBERIA;
    }

}

bool Tuberia::colisionaCon(Tuberia *otraTuberia) {
    unsigned short posXotraTuberia = otraTuberia->obtenerPosicionX();
    SDL_Rect dimensionesOtraTuberia = otraTuberia->obtenerDimensiones();
    dimensionesOtraTuberia.x += posXotraTuberia;
    dimensionesOtraTuberia.w += posXotraTuberia;
    return SDL_HasIntersection(&dimensiones,&dimensionesOtraTuberia);
}

unsigned short Tuberia::obtenerPosicionX() const {
    return posicionX;
}

SDL_Rect Tuberia::obtenerDimensiones() {
    return dimensiones;
}

tuberia_t Tuberia::serializar(){
    return {posicionX,color,tipo};
}