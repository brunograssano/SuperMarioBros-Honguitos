#ifndef SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_
#define SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_

#include "../PosicionMovil.hpp"
#include <string>
#include "../../sprites/Sprite.hpp"
#include "src/Utils/Utils.hpp"

class Enemigo{

	public:
        virtual ~Enemigo()= default;
        virtual enemigo_t serializar() =0 ;
		int obtenerPosicionX();
		int obtenerPosicionY();
		virtual void agregarPosicion(int coordenadaX,int coordenadaY);
		virtual void actualizarPosicion();

	protected:

        static float obtenerVelocidad(){
            return (0.15 + ((rand() % 11) / 100)) * pow(-1,rand()%2);
        }

		PosicionMovil* posicionActual{};
        Sprite* spriteEnemigo{};
        float velocidadX{};
        int tipoColor{};
};


#endif /* SRC_SERVER_MODELO_ENEMIGOS_ENEMIGO_HPP_ */
