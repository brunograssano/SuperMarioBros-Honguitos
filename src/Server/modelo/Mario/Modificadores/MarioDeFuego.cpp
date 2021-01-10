 #include "MarioDeFuego.hpp"
#include "SinModificador.hpp"

Disparo* MarioDeFuego::dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) {
    if(yaPuedeDisparar()){
        ciclosDisparo = 0;
        return new BolaDeFuego(posicionManosMario, direccion, velocidadDeMario);
    }else{
        return new Chispa(posicionManosMario);
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
}

bool MarioDeFuego::yaPuedeDisparar() {
    return ciclosDisparo == MAX_CICLOS_PARA_DISPARAR;
}
