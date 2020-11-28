
#ifndef SRC_MODELO_ENEMIGOS_GOOMBA_HP_
#define SRC_MODELO_ENEMIGOS_GOOMBA_HP_

using namespace std;

#include "Enemigo.hpp"
#include "../../sprites/SpriteGoomba.hpp"

class Goomba : public Enemigo{

	public:

		Goomba(int tipoColor){
			spriteEnemigo = new SpriteGoomba(tipoColor);
			this->tipoColor = tipoColor;
		}


		void actualizarPosicion()override{
			posicionActual->moverHorizontal(velocidadX);
			spriteEnemigo->actualizarSprite();
		}

		enemigo_t serializar() override{
			enemigo_t enemigoSerializado;
			enemigoSerializado.posX = this->obtenerPosicionX();
			enemigoSerializado.numeroRecorteX = spriteEnemigo->obtenerEstadoActual();
			enemigoSerializado.numeroRecorteY = tipoColor;
			enemigoSerializado.tipoEnemigo = GOOMBA;
			return enemigoSerializado;
		}


		~Goomba(){
			delete posicionActual;
			delete spriteEnemigo;
		}

	private:
		float velocidadX = -0.15;
		int tipoColor;
};

#endif /* SRC_MODELO_ENEMIGOS_GOOMBA_HP_ */
