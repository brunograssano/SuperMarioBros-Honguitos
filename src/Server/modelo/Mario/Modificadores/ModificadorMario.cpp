#include "ModificadorMario.hpp"
#include "MarioDeFuego.hpp"

ModificadorMario *ModificadorMario::hacerseDeFuego() {
    return new MarioDeFuego();
}
