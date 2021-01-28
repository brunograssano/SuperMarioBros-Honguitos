#include "ParticulaGanadores.hpp"

#include <utility>

ParticulaGanadores::ParticulaGanadores(int posX, int posY, std::string imagenAsociada, float factorAvance) {
    posicionX = posX;
    posicionY = posY;
    this->imagenAsociada = std::move(imagenAsociada);
    this->factorAvance = factorAvance;
}

void ParticulaGanadores::actualizarPosicion(int altoPantalla) {
    if(posicionY > altoPantalla){
        posicionY = 0;
    }
    posicionY += factorAvance;
}

int ParticulaGanadores::obtenerX() const {
    return posicionX;
}

int ParticulaGanadores::obtenerY() const {
    return posicionY;
}

std::string ParticulaGanadores::particulaAsociada() {
    return imagenAsociada;
}

