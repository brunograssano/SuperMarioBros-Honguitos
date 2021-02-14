#include "RecorteMarioSaltando.hpp"
#define ESTADOS_MARIO 12
#define DESPLAZAMIENTO_X 20
#define ALTO 28
#define ANCHO 20

RecorteMarioSaltando::RecorteMarioSaltando(){
    estadoActual = 0;
    inicializarEstados(ESTADOS_MARIO,DESPLAZAMIENTO_X,ALTO,ANCHO);
}

void RecorteMarioSaltando::actualizarSprite(){
    if(ciclos%5==0){
        estadoActual++;
        if(estadoActual==11 && ciclos%5==0){
            estadoActual=0;
        }
    }
    ciclos++;
}

SDL_Rect RecorteMarioSaltando::obtenerRecorte(int recorte) {
    return Recorte::obtenerRecorte(estadoActual);
}

#include "RecorteMarioSaltando.hpp"
