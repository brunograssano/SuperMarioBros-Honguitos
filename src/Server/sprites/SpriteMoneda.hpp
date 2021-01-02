
#ifndef SRC_SERVER_SPRITES_SPRITEMONEDA_HPP_
#define SRC_SERVER_SPRITES_SPRITEMONEDA_HPP_

#include <SDL2/SDL.h>

#include "Sprite.hpp"

class SpriteMoneda : public Sprite{
	public:

		SpriteMoneda();
		~SpriteMoneda() override= default;

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:
		SDL_Rect estadosPosibles[4]{};
};


#endif /* SRC_SERVER_SPRITES_SPRITEMONEDA_HPP_ */
