#include "MarioDeFuego.hpp"
#include "SinModificador.hpp"
#include "src/Server/Modelo/Juego/Mario/Mario.hpp"
#include "src/Server/Modelo/Juego/Objetos/BolaDeFuego.hpp"
#include "src/Server/Modelo/Juego/Objetos/Chispa.hpp"
#include "src/Server/Modelo/Juego/Objetos/Nada.hpp"

const int MAX_CICLOS_PARA_DISPARAR = 70;
const int MAX_CICLOS_PARA_CHISPEAR = 30;

MarioDeFuego::MarioDeFuego(Mario* referenciaAMario) {
    this->marioAsociado = referenciaAMario;
}


ObjetoFugaz* MarioDeFuego::dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) {
    if(yaPuedeDisparar()){
        ciclosDisparo = 0;
        ciclosChispa = 0;
        return new BolaDeFuego(posicionManosMario, direccion, velocidadDeMario, marioAsociado);
    }else if(yaPuedeChispear()){
        ciclosChispa = 0;
        return new Chispa(posicionManosMario, direccion);
    }else{
        return new Nada();
    }
}

ModificadorMario *MarioDeFuego::perderVida(VidaMario *vidaMario) {
    return new SinModificador(marioAsociado);
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

ModificadorMario *MarioDeFuego::hacerseDeFuego() {
    return new MarioDeFuego(marioAsociado);
}

bool MarioDeFuego::puedeAgarrarFlor() {
    return false;
}

uint8_t MarioDeFuego::serializar() {
    return MODIFICADOR_FUEGO;
}
