
#ifndef SRC_SERVER_MODELO_MONEDA_HPP_
#define SRC_SERVER_MODELO_MONEDA_HPP_

#include "../sprites/Sprite.hpp"
#include "../sprites/SpriteMoneda.hpp"
#include "Posicion.hpp"

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

	moneda_t serializar(){
		moneda_t monedaSerializada;

		monedaSerializada.posX = posicion->obtenerPosX();
		monedaSerializada.posY = posicion->obtenerPosY();
		monedaSerializada.numeroRecorte = sprite->obtenerEstadoActual();
		return monedaSerializada;
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


#endif /* SRC_SERVER_MODELO_MONEDA_HPP_ */
