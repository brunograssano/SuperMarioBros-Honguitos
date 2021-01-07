#include "MarioDeFuego.h"
#include "SinModificador.h"

void MarioDeFuego::dispararFuego(){
}

ModificadorMario *MarioDeFuego::perderVida(VidaMario *vidaMario) {
    return new SinModificador();// No pierde vida, solo pierde el estado de fuego
}
