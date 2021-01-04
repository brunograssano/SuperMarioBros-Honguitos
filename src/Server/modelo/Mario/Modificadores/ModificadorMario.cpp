#include "ModificadorMario.h"
#include "MarioDeFuego.h"

ModificadorMario *ModificadorMario::hacerseDeFuego() {
    return new MarioDeFuego();
}
