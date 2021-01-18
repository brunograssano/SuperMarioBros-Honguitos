#include "SpriteKoopa.hpp"
#define MUERTO 2

SpriteKoopa::SpriteKoopa(bool estaEspejado) {
	estadoActual = 0;
	ciclos=0;
	this->estaEspejado = estaEspejado;
}

void SpriteKoopa::actualizarSprite(){
    if(estadoActual == MUERTO){
        ciclos++;
        return;
    }
    if(ciclos>=20){
		estadoActual = 1;
		ciclos = 0;
	}
	else if(ciclos>=10){
		estadoActual = 0;
	}
	ciclos++;
}

void SpriteKoopa::morir() {
    estadoActual = MUERTO;  // todo VER CON CUAL OPCION NOS QUEDAMOS DEL SPRITE
    ciclos = 0;
}

bool SpriteKoopa::seMostroElTiempoSuficienteEnPantalla() {
    return estadoActual==MUERTO && ciclos>20;
}
