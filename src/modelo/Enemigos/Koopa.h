#ifndef SRC_MODELO_ENEMIGOS_KOOPA_H_
#define SRC_MODELO_ENEMIGOS_KOOPA_H_
using namespace std;

#include "Enemigo.h"
//#include "../../sprites/SpriteGoomba.h"

class Koopa : public Enemigo{

	public:

		Koopa(string direccionImagen){
			//spriteEnemigo = new SpriteGoomba(direccionImagen);
			this->direccionImagen = direccionImagen;
		}

		~Koopa(){
			delete spriteEnemigo;
			delete posicionActual;
		}


		void actualizarPosicion()override{
			this->posicionActual->moverHorizontal(velocidadX);
		}

	private:
		float velocidadX = 0.15;


};

#endif /* SRC_MODELO_ENEMIGOS_KOOPA_H_ */
