
#ifndef SRC_SPRITES_SPRITESORPRESA_HPP_
#define SRC_SPRITES_SPRITESORPRESA_HPP_

#include <SDL2/SDL.h>
#include "Sprite.hpp"

class SpriteSorpresa : public Sprite{
	public:

		SpriteSorpresa();
		~SpriteSorpresa(){};

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:
		SDL_Rect estadosPosibles[5];
};



#endif /* SRC_SPRITES_SPRITESORPRESA_HPP_ */
