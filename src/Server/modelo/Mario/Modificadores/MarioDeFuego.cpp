#include "MarioDeFuego.hpp"
#include "SinModificador.hpp"

Disparo* MarioDeFuego::dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) {
    return new BolaDeFuego(posicionManosMario, direccion, velocidadDeMario);
}

ModificadorMario *MarioDeFuego::perderVida(VidaMario *vidaMario) {
    return new SinModificador();// No pierde vida, solo pierde el estado de fuego
}
