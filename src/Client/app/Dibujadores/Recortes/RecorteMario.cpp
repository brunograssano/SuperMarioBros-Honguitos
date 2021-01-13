#include "RecorteMario.hpp"

const int ANCHO_IMAGEN_PIXEL = 405;
const int ALTO_IMAGEN_PIXEL = 32;
const int ANCHO_SPRITE_PIXEL = 16;
const int ALTO_SPRITE_PIXEL = 32;
const int PASO_PROXIMO_SPRITE = 30;
#define MAX_ESTADOS_MARIO 14

RecorteMario::RecorteMario(){
    inicializarEstados(MAX_ESTADOS_MARIO,PASO_PROXIMO_SPRITE,ALTO_SPRITE_PIXEL,ANCHO_SPRITE_PIXEL);
}


