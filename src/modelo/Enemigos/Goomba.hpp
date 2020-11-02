
#ifndef SRC_MODELO_ENEMIGOS_GOOMBA_HP_
#define SRC_MODELO_ENEMIGOS_GOOMBA_HP_

using namespace std;

#include "Enemigo.hpp"
#include "../../sprites/SpriteGoomba.hpp"

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

#endif /* SRC_MODELO_ENEMIGOS_GOOMBA_HP_ */
