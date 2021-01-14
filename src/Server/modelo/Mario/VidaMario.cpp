#include "VidaMario.hpp"

const int VIDAS_INICIALES = 3;

VidaMario::VidaMario() {
    vidas = VIDAS_INICIALES;
}

int VidaMario::obtenerVida() const {
    return vidas;
}

VidaMario::~VidaMario() = default;

void VidaMario::perderVida() {
    if(vidas >= 1){
        vidas--;
    }
}

bool VidaMario::estaMuerto() {
    return vidas == 0;
}
