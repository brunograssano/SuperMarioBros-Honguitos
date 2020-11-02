#ifndef SRC_MODELO_ENEMIGOS_ENEMIGO_HPP_
#define SRC_MODELO_ENEMIGOS_ENEMIGO_HPP_

#include "../Posicion.hpp"
#include "../../sprites/Sprite.hpp"
#include <string>

class Enemigo{

	public:

		int obtenerPosicionX(){
			return posicionActual->obtenerPosX();
		}

		int obtenerPosicionY(){
			return posicionActual->obtenerPosY();
		}

		Sprite* obtenerSprite(){
			return spriteEnemigo;
		}

		virtual void agregarPosicion(int coordenadaX,int coordenadaY){
			posicionActual = new PosicionMovil(coordenadaX,coordenadaY);
		};

		virtual void actualizarPosicion(){};

		virtual ~Enemigo(){};

	protected:
		PosicionMovil* posicionActual;
		string direccionImagen;
		Sprite* spriteEnemigo;

};


#endif /* SRC_MODELO_ENEMIGOS_ENEMIGO_HPP_ */
