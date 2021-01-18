#include "Recorte.hpp"

void Recorte::inicializarEstados(const int cantidadEstados,const int desplazamientoEnX,const int alto, const int ancho) {
    int desplazamiento = 0;
    for(int i = 0; i < cantidadEstados; i++){
        SDL_Rect estado;
        estado.x = desplazamiento;
        estado.y = 0;
        estado.w = ancho;
        estado.h = alto;
        desplazamiento += desplazamientoEnX;
        estadosPosibles.push_back(estado);
    }
}

int Recorte::direccion(int recorte) {
    return DERECHA;
}

SDL_Rect Recorte::obtenerRecorte(int recorte) {
    auto iterador = estadosPosibles.begin();
    SDL_Rect estado;
    if(recorte == 0){
        estado = *iterador;
    }else{
        std::advance(iterador, recorte);
        estado = *iterador;
    }
    return estado;
}

int Recorte::obtenerAnchuraParaDibujarImagen(int tipo) {
    SDL_Rect rectangulo = estadosPosibles.front();
    return rectangulo.w;
}

int Recorte::obtenerAlturaParaDibujarImagen(int tipo) {
    SDL_Rect rectangulo = estadosPosibles.front();
    return rectangulo.h;
}

SDL_Rect Recorte::obtenerRecorte(int recorte, int color) {
    auto iterador = estadosPosibles.begin();
    SDL_Rect estado;
    if(recorte == 0){
        estado = *iterador;
    }else{
        std::advance(iterador, recorte);
        estado = *iterador;
    }
    estado.y = color * estado.h;
    return estado;
}

