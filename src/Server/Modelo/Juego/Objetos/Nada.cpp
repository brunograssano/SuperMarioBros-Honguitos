#include "Nada.hpp"

Nada::Nada() = default;
Nada::~Nada() = default;

void Nada::actualizar() {}

entidad_t Nada::serializar() {
    return {0, 0, NADA, 0,0,false};
}

int Nada::obtenerPosicionX() {
    return 0;
}

bool Nada::debeDesaparecer() {
    return true;
}

int Nada::tipoDeEfecto() {
    return NADA;
}
