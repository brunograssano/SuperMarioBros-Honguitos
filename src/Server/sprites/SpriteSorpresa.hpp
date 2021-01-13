
#ifndef SRC_SERVER_SPRITES_SPRITESORPRESA_HPP_
#define SRC_SERVER_SPRITES_SPRITESORPRESA_HPP_

#include <SDL2/SDL.h>

#include "SpriteBloque.hpp"

class SpriteSorpresa : public SpriteBloque{
	public:

		explicit SpriteSorpresa();
		~SpriteSorpresa() override= default;
		SDL_Rect obtenerRectanguloActual()override;
		void actualizarSprite()override;
		void usarse() override;
		bool cambioElSprite() override;

	private:
		SDL_Rect estadosPosibles[5]{};
};



#endif /* SRC_SERVER_SPRITES_SPRITESORPRESA_HPP_ */
