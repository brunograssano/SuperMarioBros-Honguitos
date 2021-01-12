
#ifndef SRC_SERVER_SPRITES_SPRITELADRILLO_HPP_
#define SRC_SERVER_SPRITES_SPRITELADRILLO_HPP_

#include <SDL2/SDL.h>

#include "Sprite.hpp"

class SpriteLadrillo : public Sprite{
	public:
		explicit SpriteLadrillo(int tipo);
		~SpriteLadrillo() override = default;
		SDL_Rect obtenerRectanguloActual()override;
		void actualizarSprite()override;

};


#endif /* SRC_SERVER_SPRITES_SPRITELADRILLO_HPP_ */
