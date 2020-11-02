
#ifndef SRC_SPRITES_SPRITEMONEDA_HPP_
#define SRC_SPRITES_SPRITEMONEDA_HPP_

#include <SDL2/SDL.h>
#include "Sprite.hpp"

class SpriteMoneda : public Sprite{
	public:

		SpriteMoneda();
		~SpriteMoneda(){};

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:
		SDL_Rect estadosPosibles[4];
};


#endif /* SRC_SPRITES_SPRITEMONEDA_HPP_ */
