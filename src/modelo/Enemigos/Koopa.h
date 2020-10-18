#ifndef SRC_MODELO_ENEMIGOS_KOOPA_H_
#define SRC_MODELO_ENEMIGOS_KOOPA_H_
using namespace std;

#include "Enemigo.h"
#include <string>

class Koopa : public Enemigo{

	public:

		Koopa(string direccionImagen){
			this->direccionImagen = direccionImagen;
		}

		~Koopa(){
			delete this->posicionActual;
		}

		void actualizarPosicion()override{
			this->posicionActual->moverHorizontal(velocidadX);
		}

	private:
		float velocidadX = 0.05;
		string direccionImagen;

};

#endif /* SRC_MODELO_ENEMIGOS_KOOPA_H_ */
