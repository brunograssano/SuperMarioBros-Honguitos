
#ifndef SRC_SERVER_SPRITES_SPRITESORPRESA_HPP_
#define SRC_SERVER_SPRITES_SPRITESORPRESA_HPP_

#include <SDL2/SDL.h>

#include "Sprite.hpp"

class SpriteSorpresa : public Sprite{
	public:

		explicit SpriteSorpresa(bool seUso);
		~SpriteSorpresa() override= default;
		SDL_Rect obtenerRectanguloActual()override;
		void actualizarSprite()override;

	private:
		SDL_Rect estadosPosibles[5]{};
};



#endif /* SRC_SERVER_SPRITES_SPRITESORPRESA_HPP_ */
