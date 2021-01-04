#ifndef SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_
#define SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_

using namespace std;
#include <list>
#include <string>

#include "../../../Utils/Utils.hpp"

#include "../Posicion.hpp"
#include "../../sprites/Sprite.hpp"
#include "../../sprites/SpriteSorpresa.hpp"
#include "../../sprites/SpriteLadrillo.hpp"

#define SORPRESA 0

class Bloque{
    public:

		virtual ~Bloque(){};

		int obtenerPosicionX(){
			return this->posicion->obtenerPosX();
		}
		int obtenerPosicionY(){
			return this->posicion->obtenerPosY();
		}

		Sprite* obtenerSprite(){
			return this->spriteBloque;
		}

		virtual bloque_t serializar(){return {0,0,0,0};};

		void ubicarEnPosicionDefault(){
			delete this->posicion;
			this->posicion = new PosicionFija(200, 200);
		}

    protected:
    	Posicion* posicion;
    	Sprite* spriteBloque;

		static int normalizarCoordenadaIngresada(int coordenada){
			return (coordenada/40)*40;
		}
};

#endif /* SRC_SERVER_MODELO_BLOQUES_BLOQUE_HPP_ */