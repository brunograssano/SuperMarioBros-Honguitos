#include "SinModificador.hpp"
#include "MarioDeFuego.hpp"

ModificadorMario *SinModificador::perderVida(VidaMario *vidaMario) {
    vidaMario->perderVida();
    return new SinModificador();
}

Disparo *SinModificador::dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) {
    return new BolaDeFuego(posicionManosMario, direccion, velocidadDeMario);
    //return new Chispa(posicionManosMario); //todo
}
