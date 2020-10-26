
#ifndef SRC_MODELO_ENEMIGOS_GOOMBA_H_
#define SRC_MODELO_ENEMIGOS_GOOMBA_H_
using namespace std;

#include "Enemigo.h"
#include "../../sprites/SpriteGoomba.h"

class Goomba : public Enemigo{

	public:

		Goomba(string direccionImagen){
			spriteEnemigo = new SpriteGoomba(direccionImagen);
		}



		void actualizarPosicion()override{
			posicionActual->moverHorizontal(velocidadX);
			spriteEnemigo->actualizarSprite();
		}

		~Goomba(){
			delete posicionActual;
			delete spriteEnemigo;
		}

	private:
		float velocidadX = -0.15;

};

#endif /* SRC_MODELO_ENEMIGOS_GOOMBA_H_ */
