#include "VidaMario.h"

const int VIDAS_INICIALES = 3;

VidaMario::VidaMario() {
    vidas = VIDAS_INICIALES;
}

int VidaMario::obtenerVida() {
    return vidas;
}

VidaMario::~VidaMario() {

}

void VidaMario::perderVida() {
    vidas--;
}
