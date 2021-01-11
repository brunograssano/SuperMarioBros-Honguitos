#include "SinModificador.hpp"
#include "MarioDeFuego.hpp"

ModificadorMario *SinModificador::perderVida(VidaMario *vidaMario) {
    vidaMario->perderVida();
    return new SinModificador();
}

Disparo *SinModificador::dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) {
    if(yaPuedeChispear()){
        ciclosChispa = 0;
        return new Chispa(posicionManosMario, direccion);
    }else {
        return new Nada();
    }
}

void SinModificador::actualizar(){
    ciclosChispa++;
    if(ciclosChispa > MAX_CICLOS_PARA_CHISPEAR){
        ciclosChispa = MAX_CICLOS_PARA_CHISPEAR;
    }
}

bool SinModificador::yaPuedeChispear() {
    return ciclosChispa == MAX_CICLOS_PARA_CHISPEAR;
}
