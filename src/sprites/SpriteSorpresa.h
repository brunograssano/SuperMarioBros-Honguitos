
#ifndef SRC_SPRITES_SPRITESORPRESA_H_
#define SRC_SPRITES_SPRITESORPRESA_H_

#include "Sprite.h"
#include <SDL2/SDL.h>

class SpriteSorpresa : public Sprite{
	public:

		SpriteSorpresa();
		~SpriteSorpresa(){};

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:

		bool cambio;
		int ciclos;
		int estadoActual;
		SDL_Rect estadosPosibles[5];
};



#endif /* SRC_SPRITES_SPRITESORPRESA_H_ */
