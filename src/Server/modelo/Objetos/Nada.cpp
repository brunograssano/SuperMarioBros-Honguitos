#include "Nada.hpp"

Nada::Nada() = default;
Nada::~Nada() = default;

void Nada::actualizar() {}

efecto_t Nada::serializar() {
    return {0, 0, 0, 0};
}

int Nada::obtenerPosicionX() {
    return 0;
}

bool Nada::debeDesaparecer() {
    return true;
}
