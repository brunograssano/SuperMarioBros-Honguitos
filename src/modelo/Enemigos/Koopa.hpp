#ifndef SRC_MODELO_ENEMIGOS_KOOPA_HPP_
#define SRC_MODELO_ENEMIGOS_KOOPA_HPP_

using namespace std;

#include "Enemigo.hpp"
#include "../../sprites/SpriteKoopa.hpp"


class Koopa : public Enemigo{

	public:

		Koopa(int tipo){
			spriteEnemigo = new SpriteKoopa(tipo);
		}

		~Koopa(){
			delete spriteEnemigo;
			delete posicionActual;
		}


		void actualizarPosicion()override{
			posicionActual->moverHorizontal(velocidadX);
			spriteEnemigo->actualizarSprite();
		}

	private:
		float velocidadX = -0.15;


};

#endif /* SRC_MODELO_ENEMIGOS_KOOPA_HPP_ */
