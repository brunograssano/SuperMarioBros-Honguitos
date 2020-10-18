
#ifndef SRC_MODELO_ENEMIGOS_GOOMBA_H_
#define SRC_MODELO_ENEMIGOS_GOOMBA_H_
using namespace std;

#include "Enemigo.h"
#include <string>

class Goomba : public Enemigo{

	public:

		Goomba(string direccionImagen){
			this->direccionImagen = direccionImagen;
		}



		void actualizarPosicion()override{
			this->posicionActual->moverHorizontal(velocidadX);
		}

		~Goomba(){
			delete this->posicionActual;
		}
	private:
		float velocidadX = 0.05;
		string direccionImagen;
};

#endif /* SRC_MODELO_ENEMIGOS_GOOMBA_H_ */
