#include "SpriteKoopa.hpp"
#include "src/Server/Modelo/Juego/Nivel/Enemigos/Koopa.hpp"

#define TIERRA_1 0
#define TIERRA_2 1
#define AIRE_1 2
#define AIRE_2 3
#define MUERTO 4

SpriteKoopa::SpriteKoopa(bool estaEspejado, Koopa* koopaAsociado) {
	estadoActual = 0;
	ciclos=0;
	this->estaEspejado = estaEspejado;
	this->koopa = koopaAsociado;
}

void SpriteKoopa::actualizarSprite(){
    if(estadoActual != MUERTO){
        if(koopa->estaEnElAire()){
            actualizarSpriteAire();
        }else{
            actualizarSpriteTierra();
        }
    }
    ciclos++;
}

void SpriteKoopa::morir() {
    estadoActual = MUERTO;
    ciclos = 0;
}

bool SpriteKoopa::seMostroElTiempoSuficienteEnPantalla() {
    return estadoActual==MUERTO && ciclos>20;
}

void SpriteKoopa::actualizarSpriteAire() {
    if(estadoActual != AIRE_1 && estadoActual != AIRE_2){
        ciclos = 0;
        estadoActual = AIRE_1;
    }else if(ciclos>=10) {
        ciclos = 0;
        estadoActual = (estadoActual==AIRE_1)?AIRE_2:AIRE_1;
    }
}

void SpriteKoopa::actualizarSpriteTierra() {
    if(estadoActual != TIERRA_1 && estadoActual != TIERRA_2){
        ciclos = 0;
        estadoActual = TIERRA_1;
    }else if(ciclos>=10) {
        ciclos = 0;
        estadoActual = (estadoActual==TIERRA_1)?TIERRA_2:TIERRA_1;
    }
}
