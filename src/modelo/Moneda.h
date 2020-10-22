
#ifndef SRC_MODELO_MONEDA_H_
#define SRC_MODELO_MONEDA_H_

#include "Posicion.h"
#include "../sprites/Sprite.h"
#include "../sprites/SpriteMoneda.h"

class Moneda{

public:
	Moneda(int coordenadaX, int coordenadaY){
		this->posicion = new PosicionFija(coordenadaX, coordenadaY);
		this->sprite = new SpriteMoneda();
	}

	~Moneda(){
		delete this->posicion;
		delete this->sprite;
	}

	Sprite* obtenerSprite(){
		return this->sprite;
	}

	int obtenerPosicionX(){
		return this->posicion->obtenerPosX();
	}

	int obtenerPosicionY(){
		return this->posicion->obtenerPosY();
	}

private:
	Posicion* posicion;
	Sprite* sprite;
};


#endif /* SRC_MODELO_MONEDA_H_ */
