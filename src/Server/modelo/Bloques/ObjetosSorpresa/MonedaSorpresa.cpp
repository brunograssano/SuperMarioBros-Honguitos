#include "MonedaSorpresa.hpp"

MonedaSorpresa::MonedaSorpresa() {
    _debeDesaparecer = true;
}

void MonedaSorpresa::usarse(Mario *mario) {
    mario->agregarMoneda();
}

efecto_t MonedaSorpresa::serializar() {
    return {0, 0, 0, 0};
}

void MonedaSorpresa::actualizar() {
}

int MonedaSorpresa::obtenerPosicionX() {
    return 0;
}
