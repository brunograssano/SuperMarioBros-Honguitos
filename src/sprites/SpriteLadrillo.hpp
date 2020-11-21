
#ifndef SRC_SPRITES_SPRITELADRILLO_HPP_
#define SRC_SPRITES_SPRITELADRILLO_HPP_

#include <SDL2/SDL.h>
#include "Sprite.hpp"

class SpriteLadrillo : public Sprite{
	public:

		SpriteLadrillo(int tipo);
		SpriteLadrillo();
		~SpriteLadrillo(){};

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:

		SDL_Rect rectanguloLadrillo;

};


#endif /* SRC_SPRITES_SPRITELADRILLO_HPP_ */
