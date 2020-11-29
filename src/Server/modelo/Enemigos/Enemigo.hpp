#ifndef SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_
#define SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_

#include "../Posicion.hpp"
#include <string>
#include "../../sprites/Sprite.hpp"

#define TIPO_GOOMBA 1
#define TIPO_KOOPA 2


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

		virtual enemigo_t serializar(){return {0,0,0,0};};

		virtual void actualizarPosicion(){};

		virtual ~Enemigo(){};

	protected:
		PosicionMovil* posicionActual;
		string direccionImagen;
		Sprite* spriteEnemigo;
};


#endif /* SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_ */
