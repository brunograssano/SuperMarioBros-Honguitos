#include "SpriteGoomba.hpp"
#define MUERTO 2

SpriteGoomba::SpriteGoomba(){
	estadoActual = 0;
	ciclos=0;
}

void SpriteGoomba::actualizarSprite(){
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

void SpriteGoomba::morir() {
    estadoActual = MUERTO;
    ciclos = 0;
}

bool SpriteGoomba::seMostroElTiempoSuficienteEnPantalla() {
    return estadoActual==MUERTO && ciclos>20;
}
