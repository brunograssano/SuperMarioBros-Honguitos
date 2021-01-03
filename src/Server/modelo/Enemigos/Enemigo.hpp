#ifndef SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_
#define SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_

#include "../Posicion.hpp"
#include <string>
#include "../../sprites/Sprite.hpp"
#include "src/Utils/Utils.hpp"

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

		virtual enemigo_t serializar(){return {0,0,0,0,0};}

		virtual void actualizarPosicion(){};

		virtual ~Enemigo(){};

	protected:

        float obtenerVelocidad(){
            return (0.15 + ((rand() % 11) / 100)) * pow(-1,rand()%2);
        }

		PosicionMovil* posicionActual;
        Sprite* spriteEnemigo;
        string direccionImagen;//revisar que pasa
        float velocidadX;
        int tipoColor;
};


#endif /* SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_ */
