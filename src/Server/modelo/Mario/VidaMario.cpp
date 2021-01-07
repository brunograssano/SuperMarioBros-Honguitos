#include "VidaMario.h"

const int VIDAS_INICIALES = 3;

VidaMario::VidaMario() {
    vidas = VIDAS_INICIALES;
}

int VidaMario::obtenerVida() const {
    return vidas;
}

VidaMario::~VidaMario() = default;

void VidaMario::perderVida() {
    vidas--;
}
