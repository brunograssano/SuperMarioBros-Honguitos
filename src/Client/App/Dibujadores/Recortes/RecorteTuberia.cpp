#include "RecorteTuberia.hpp"
#include "src/Utils/Constantes.hpp"

#define ALTO_TUBERIA_IMAGEN 66
#define ANCHO_TUBERIA_CHICA_IMAGEN 33
#define ANCHO_TUBERIA_GRANDE_IMAGEN 67

const int DESPLAZAMIENTO_X = 33;

RecorteTuberia::RecorteTuberia() {
    SDL_Rect primerEstado = {0,0, ANCHO_TUBERIA_CHICA_IMAGEN, ALTO_TUBERIA_IMAGEN};
    SDL_Rect segundoEstado = {DESPLAZAMIENTO_X, 0, ANCHO_TUBERIA_GRANDE_IMAGEN, ALTO_TUBERIA_IMAGEN};
    estadosPosibles.push_back(primerEstado);
    estadosPosibles.push_back(segundoEstado);
}

int RecorteTuberia::obtenerAlturaParaDibujarImagen(int recorteX, int recorteY) {
    if(recorteX == TUBERIA_CHICA){
        return ALTO_TUBERIA_CHICA*2; // Esto es por cómo está hecha la imagen... y el constructor.
    }else{
        return ALTO_TUBERIA_GRANDE;
    }
}

int RecorteTuberia::obtenerAnchuraParaDibujarImagen(int recorteX, int recorteY) {
    if(recorteX == TUBERIA_CHICA){
        return ANCHO_TUBERIA_CHICA;
    }else{
        return ANCHO_TUBERIA_GRANDE;
    }
}