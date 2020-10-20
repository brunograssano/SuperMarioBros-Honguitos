#ifndef SRC_MODELO_ENEMIGOS_KOOPA_H_
#define SRC_MODELO_ENEMIGOS_KOOPA_H_
using namespace std;

#include "Enemigo.h"
#include "../../sprites/SpriteKoopa.h"


class Koopa : public Enemigo{

	public:

		Koopa(string direccionImagen){
			spriteEnemigo = new SpriteKoopa(direccionImagen);
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
		float velocidadX = 0.15;


};

#endif /* SRC_MODELO_ENEMIGOS_KOOPA_H_ */
