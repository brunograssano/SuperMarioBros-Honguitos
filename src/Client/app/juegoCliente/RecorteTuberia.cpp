#include "RecorteTuberia.hpp"

#define ALTO_TUBERIA 66

RecorteTuberia::RecorteTuberia() {
    int desplazamientoX = 0;
    for(int i=0; i<MAX_TIPOS;i++){
            recortesTuberias[i].x = desplazamientoX;
            recortesTuberias[i].y = ALTO_TUBERIA;
            recortesTuberias[i].w= i == 0 ? 33 : 67;
            recortesTuberias[i].h= ALTO_TUBERIA;
            desplazamientoX += 33;
    }
}

SDL_Rect RecorteTuberia::obtenerRecorte(uint8_t tipo, uint8_t color) {
    SDL_Rect recorte = recortesTuberias[tipo];
    recorte.y *= color;
    return recorte;
}


