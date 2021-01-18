#include "Plataforma.hpp"
#include "src/Utils/Constantes.hpp"

Plataforma::Plataforma(int comienzoPlataformaX,int finPlataformaX,int alto) {
    rangoPlataforma = {comienzoPlataformaX,finPlataformaX,0,alto,alto,finPlataformaX-comienzoPlataformaX};
}

rectangulo_t Plataforma::obtenerRectangulo() {
    return rangoPlataforma;
}

void Plataforma::inicializarMapasDeColision(){}

string Plataforma::obtenerColisionID() {
    return COLISION_ID_PLATAFORMA;
}

bool Plataforma::debeColisionar() {
    return true;
}
