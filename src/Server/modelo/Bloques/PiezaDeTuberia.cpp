#include "PiezaDeTuberia.hpp"

#include "src/Utils/Constantes.hpp"

PiezaDeTuberia::PiezaDeTuberia(int posX, int posY, int w, int h) {
    rectangulo = {posX, posX+w, posY, posY+h, h, w};
    inicializarMapasDeColision();
}

bool PiezaDeTuberia::debeColisionar() {
    return true;
}

rectangulo_t PiezaDeTuberia::obtenerRectangulo() {
    return rectangulo;
}

string PiezaDeTuberia::obtenerColisionID() {
    return COLISION_ID_PIEZA_TUBERIA;
}

void PiezaDeTuberia::inicializarMapasDeColision() {

}

void PiezaDeTuberia::elevar(int y) {
    rectangulo.y1 += y;
    rectangulo.y2 += y;
}
