#include "SinModificador.h"
#include "MarioDeFuego.h"

void SinModificador::dispararFuego() {
    // no se hace nada aca
}

ModificadorMario *SinModificador::perderVida(VidaMario *vidaMario) {
    vidaMario->perderVida();
    return new SinModificador();
}

