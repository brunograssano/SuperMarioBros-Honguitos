#include "SinModificador.hpp"
#include "MarioDeFuego.hpp"

ModificadorMario *SinModificador::perderVida(VidaMario *vidaMario) {
    vidaMario->perderVida();
    return new SinModificador();
}

Disparo *SinModificador::dispararFuego(Posicion posicionManosMario) {
    return new Chispa(posicionManosMario);
}

