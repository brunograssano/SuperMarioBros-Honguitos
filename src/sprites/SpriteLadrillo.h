
#ifndef SRC_SPRITES_SPRITELADRILLO_H_
#define SRC_SPRITES_SPRITELADRILLO_H_

#include "Sprite.h"
#include <SDL2/SDL.h>

class SpriteLadrillo : public Sprite{
	public:

		SpriteLadrillo();
		~SpriteLadrillo(){};

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:

		SDL_Rect rectanguloLadrillo;

};


#endif /* SRC_SPRITES_SPRITELADRILLO_H_ */
