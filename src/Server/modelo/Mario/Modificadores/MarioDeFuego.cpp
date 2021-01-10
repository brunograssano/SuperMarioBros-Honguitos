 #include "MarioDeFuego.hpp"
#include "SinModificador.hpp"

Disparo* MarioDeFuego::dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) {
    if(yaPuedeDisparar()){
        ciclosDisparo = 0;
        ciclosChispa = 0;
        return new BolaDeFuego(posicionManosMario, direccion, velocidadDeMario);
    }else if(yaPuedeChispear()){
        ciclosChispa = 0;
        return new Chispa(posicionManosMario, direccion);
    }else{
        return new Nada();
    }
}

ModificadorMario *MarioDeFuego::perderVida(VidaMario *vidaMario) {
    return new SinModificador();
}

void MarioDeFuego::actualizar() {
    ciclosDisparo++;
    if(ciclosDisparo > MAX_CICLOS_PARA_DISPARAR){
        ciclosDisparo = MAX_CICLOS_PARA_DISPARAR;
    }
    ciclosChispa++;
    if(ciclosChispa > MAX_CICLOS_PARA_CHISPEAR){
        ciclosChispa = MAX_CICLOS_PARA_CHISPEAR;
    }
}

bool MarioDeFuego::yaPuedeDisparar() const {
    return ciclosDisparo == MAX_CICLOS_PARA_DISPARAR;
}

bool MarioDeFuego::yaPuedeChispear() const {
    return ciclosChispa == MAX_CICLOS_PARA_CHISPEAR;
}
