#include "MarioDeFuego.hpp"
#include "SinModificador.hpp"

Disparo* MarioDeFuego::dispararFuego(Posicion posicionManosMario){
    return new BolaDeFuego(posicionManosMario);
}

ModificadorMario *MarioDeFuego::perderVida(VidaMario *vidaMario) {
    return new SinModificador();// No pierde vida, solo pierde el estado de fuego
}
