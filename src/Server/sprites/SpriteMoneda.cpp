
#include "SpriteMoneda.hpp"

SpriteMoneda::SpriteMoneda(){
    this->ciclos = 0;
	this->estadoActual = 2;
}


void SpriteMoneda::actualizarSprite(){
	if(ciclos>=40){
		estadoActual = 3;
		ciclos = 0;
	}else if(ciclos>=30){
		estadoActual = 2;
	}else if(ciclos>=20){
		estadoActual = 1;
	}else if(ciclos>=10){
		estadoActual = 0;
	}
	ciclos++;
}


