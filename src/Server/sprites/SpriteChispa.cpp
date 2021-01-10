#include "SpriteChispa.hpp"

#define ESTADO_INICIAL 0

SpriteChispa::SpriteChispa(int direccion){
    this->direccionTextura = "resources/Imagenes/Objetos/Chispa.png";
    this->ciclos = 0;
    this->estadoActual = ESTADO_INICIAL;
    this->direccion = direccion;

    int corrimientoEnImagen = 0;
    for(auto & estadosPosible : estadosPosibles){
        estadosPosible.x = corrimientoEnImagen;
        estadosPosible.y = 0;
        estadosPosible.w = 31;
        estadosPosible.h = 22;
        corrimientoEnImagen+= 32;
    }

}
void SpriteChispa::cambiarSprite() {
    if(estadoActual == 3){
        estadoActual = 2;
    }else{
        estadoActual++;
    }
}

void SpriteChispa::actualizarSprite() {
    if(ciclos >= CICLOS_PARA_CAMBIO) {
        cambiarSprite();
        ciclos = 0;
    }
    ciclos++;
}

SDL_Rect SpriteChispa::obtenerRectanguloActual() {
    return estadosPosibles[estadoActual];
}

int SpriteChispa::obtenerEstadoActual() {
    if(direccion == DERECHA){
        return estadoActual;
    }else{
        return estadoActual + 4; //Implica que está mirando hacia la izquierda.
    }
}


