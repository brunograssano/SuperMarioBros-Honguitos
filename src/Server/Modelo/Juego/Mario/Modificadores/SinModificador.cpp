#include "SinModificador.hpp"
#include "MarioDeFuego.hpp"
#include "src/Server/Modelo/Juego/Mario/Mario.hpp"
#include "src/Server/Modelo/Juego/Objetos/Chispa.hpp"
#include "src/Server/Modelo/Juego/Objetos/Nada.hpp"

const int MAX_CICLOS_PARA_CHISPEAR = 30;

SinModificador::SinModificador(Mario *marioAsociado) {
    this->marioAsociado = marioAsociado;
}

ModificadorMario *SinModificador::perderVida(VidaMario *vidaMario) {
    vidaMario->perderVida();
    return new SinModificador(marioAsociado);
}

ObjetoFugaz *SinModificador::dispararFuego(PosicionFija posicionManosMario, int direccion, float velocidadDeMario) {
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

bool SinModificador::yaPuedeChispear() const {
    return ciclosChispa == MAX_CICLOS_PARA_CHISPEAR;
}

ModificadorMario *SinModificador::hacerseDeFuego() {
    return new MarioDeFuego(marioAsociado);
}

bool SinModificador::puedeAgarrarFlor() {
    return true;
}

uint8_t SinModificador::serializar() {
    return SIN_MODIFICADOR;
}
